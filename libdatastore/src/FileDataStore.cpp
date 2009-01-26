/*
 *  FileDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../libdatastore/include/FileDataStore.h"
FileDataStore::FileDataStore(int Kind) {
	if (Kind==KIND_INPUT) {
		//setup for input of data
		init=true;
	} else if (Kind==KIND_OUTPUT) {
		//setup for output of data
		init=true;
	}
}
FileDataStore::FileDataStore(string FileName, int Kind, bool Piped) {
	filename=FileName;
	pipe=Piped;
	if (Kind==KIND_INPUT) {
		//setup for input of data
		init=true;
	} else if (Kind==KIND_OUTPUT) {
		//setup for output of data
		init=true;
	}
}
bool FileDataStore::GetDataAsTimetable(int Year){
	if (kind==KIND_OUTPUT) {
		return false;
	}
	return true;
}
bool FileDataStore::WriteTimetable(Timetable * TheTimetable) {
	if (kind==KIND_INPUT) {
		return false;
	}
	// declarations
	list<Course> courses = *(TheTimetable->Get());
	list<Class> classes;
	list<Course>::iterator i;
	list<Class>::iterator j;
	// open the file for writing and write out calendar header
	// calendar header
	string header[25]= {
	"BEGIN:VCALENDAR",
	"METHOD:PUBLISH",
	"X-WR-TIMEZONE:Canada/Eastern",
	"PRODID:-//Kevin Ross//Timetabler//EN",
	"CALSCALE:GREGORIAN",
	"X-WR-CALNAME:School Schedule",
	"X-WR-CALDESC:My class schedule",
	"VERSION:2.0",
	"BEGIN:VTIMEZONE",
	"TZID:America/Toronto",
	"BEGIN:DAYLIGHT",
	"TZOFFSETFROM:-0500",
	"TZOFFSETTO:-0400",
	"DTSTART:20070311T020000",
	"RRULE:FREQ=YEARLY;BYMONTH=3;BYDAY=2SU",
	"TZNAME:EDT",
	"END:DAYLIGHT",
	"BEGIN:STANDARD",
	"TZOFFSETFROM:-0400",
	"TZOFFSETTO:-0500",
	"DTSTART:20071104T020000",
	"RRULE:FREQ=YEARLY;BYMONTH=11;BYDAY=1SU",
	"TZNAME:EST",
	"END:STANDARD",
	"END:VTIMEZONE"};
	datastore.clear();
	for (int i = 0; i < 25; i++) {
		datastore.push_back(header[i]);
	}
	for (i=courses.begin(); i != courses.end(); i++) {
		classes=*((*i).Get());
		for (j=classes.begin(); j != classes.end(); j++) {
			// easiest way is to use a template hardcoded into the program
			/*
			 BEGIN:VEVENT
			 SEQUENCE:3
			 TRANSP:OPAQUE
			 UID:2E97FB8A-9B4E-4DC5-8888-BEC12B57FC1C
			 DTSTART;TZID=America/Toronto:20080922T200000
			 STATUS:CONFIRMED
			 DTSTAMP:20080919T024343Z
			 SUMMARY:CourseName Type
			 COMMENT:CourseCode Section
			 DTEND;TZID=America/Toronto:20080922T210000
			 RRULE:FREQ=WEEKLY;INTERVAL=1
			 END:VEVENT
			*/
			// using RRULE:FREQ=WEEKLY;UNTIL=20021214T055959;INTERVAL=1;BYDAY=MO,TU,WE,TH allows for every Wednesday type stuff
			// header and starttime,endtime
			datastore.push_back("BEGIN:VEVENT\nDTSTART;TZID=America/Toronto:" + Date::GetRfcTime(&(j->GetData()->startday), &(j->GetData()->start)));
			datastore.push_back("DTEND;TZID=America/Toronto:" + Date::GetRfcTime(&(j->GetData()->startday), &(j->GetData()->end)));
			// summary: course name and class type and section
			datastore.push_back("SUMMARY:" + j->GetData()->type + "(" + Common::int2str(j->GetData()->section) + ")" + "\\, " + i->GetData().name);
			// comment: course code and section + prof
			datastore.push_back("DESCRIPTION:"+i->GetData().code+" "+i->GetData().section+" Prof: "+j->GetData()->instructor+"\\N");
			// the entire class and course info to make it easily parseable
			datastore.push_back("	$DO NOT MODIFY ANYTHING AFTER THIS LINE!$\\N");
			datastore.push_back(" " + MakeLineLength(i->ToEncodedString()) + "\\N");
			datastore.push_back(" " + MakeLineLength(j->ToEncodedString()));
			// location
			datastore.push_back("LOCATION:"+j->GetData()->location+" "+j->GetData()->room);
			// recurrance
			datastore.push_back("RRULE:FREQ=WEEKLY;INTERVAL=1;UNTIL="+Date::GetRfcTime(&(j->GetData()->endday), &(j->GetData()->end)));
			datastore.push_back("END:VEVENT");
		}
	}
	datastore.push_back("END:VCALENDAR");
	if (!pipe) {
		fstream fout;
		fout.open(filename.c_str(), ios::out | ios::trunc);
		if (!fout.is_open()) {
			return false;
		}
		list<string>::iterator k;
		for (k=datastore.begin(); k != datastore.end(); k++) {
			fout << (*k) << endl;
		}
		fout.close();
	}
	return true;
}
FileDataStore::~FileDataStore() {
}
string FileDataStore::MakeLineLength(string Input) {
	string Output="";
	// make it 70 chars in length
	for (int i = 0; i<Input.length(); i++) {
		Output+=Input.c_str()[i];
		if (i%70==0 && i!=0) {
			Output+="\n ";
		}
	}
	return Output;
}