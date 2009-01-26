/*
 *  RabaskaDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 07/01/09.
 *  Copyright 2009 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <pme.h>
#include "../../libdatastore/include/RabaskaDataStore.h"
#include "../../libtimetable/include/Timetable.h"
RabaskaDataStore::RabaskaDataStore(int Kind) {
	kind=KIND_INPUT;
	init=true;
}
RabaskaDataStore::RabaskaDataStore(string FileName, int Kind, bool Piped){
	kind=KIND_INPUT;
	datastore.clear();
	pipe=Piped;
	if (!pipe) {
		init=ReadFile(FileName);
	}
}
string TrimSpaces(string str) {
	// use regexp because I know the input
	PME trimmer("([A-Z][A-Z][A-Z]) ([0-9][0-9][0-9][0-9])","");
	trimmer.match(str);
	return string(trimmer[1]+trimmer[2]);
}
bool RabaskaDataStore::GetDataAsTimetable(int Year){
	// datere: 1=sm, 2=sd, 3=em, 4=ed
	string datere = "([A-Z][a-z][a-z]) ([0-9]?[0-9]) ([A-Z][a-z][a-z]) ([0-9]?[0-9])";
	// coursere: 1=code, 2=section, 3=name
	string headerre = "([A-Z][A-Z][A-Z] [0-9][0-9][0-9][0-9])[ \t]*" // course code
	"([A-Z][A-Z]? )?[ \t]*" // section
	"([A-Za-z0-9 ]*)(.*)"; // name
	// classre: 1=type, 2=section, 3=day, 4=starth, 5=startm, 6=endh, 7=endm, 8=b, 9=r, 10=pl, 11=pf
	string classre = "\t([A-Z][A-Z][A-Z]) \\(([0-9])\\) \t" // type, section
	"([A-Z][a-z][a-z]) \t" // day
	"(\\d\\d):(\\d\\d) \t(\\d\\d):(\\d\\d) \t" //time
	"([A-Z][A-Z][A-Z]) " // location
	"([A-Za-z0-9]*) \t" // room
	"([^,]*), (.*)"; // prof
	PME dateex(datere.c_str(),"");
	PME headerex(headerre.c_str(),"");
	PME classex(classre.c_str(),"");
	string currentcourse = "";
	string currentdate = "";
	list<string> currentclass;
	list<string>::iterator lines = datastore.begin();
	bool eof = true;
	Timetable * Return = new Timetable(Year);
	currentdate=*lines;
	lines++;
	while (eof) {
		currentcourse=*lines;
		lines++;
		lines++;
		while (classex.match(*lines)>0 && eof) {
			currentclass.push_back(*lines);
			if (*lines==datastore.back()) {
				eof=false;
			} else {
				lines++;
			}
		}
		list<string>::iterator i;
		// doesn't match rabaska format, return empty timetable
		if (headerex.match(currentcourse)==0||dateex.match(currentdate)==0||currentclass.size()==0) {
			return false;
		}
		Date StartD, EndD, iStartD,iEndD;
		iStartD = Date(Common::str2int(dateex[2]),Date::MonthFromName(dateex[1]),Year);
		iEndD =  Date(Common::str2int(dateex[4]),Date::MonthFromName(dateex[3]),Year);
		Course * NewCourse = new Course(headerex[3],TrimSpaces(headerex[1]),headerex[2]);
		Class * NewClass;
		list<string>::iterator curclass;
		for (curclass=currentclass.begin(); curclass!=currentclass.end(); curclass++) {
			classex.match(*curclass);
			StartD=Date::GetNearestDay(iStartD,Date::ThreeLetterDayToFullName(classex[3]));
			EndD=iEndD;
			// classre: 1=type, 2=section, 3=day, 4=starth, 5=startm, 6=endh, 7=endm, 8=b, 9=r, 10=pl, 11=pf
			// class: Day, TStart, TEnd, StartD, EndD, Rec, Type, Section, Location, Room, Instructor
			NewClass = new Class(Date::ThreeLetterDayToFullName(classex[3]),Time(classex[4],classex[5]),Time(classex[6],classex[7]),
								 StartD, EndD, 1, classex[1], Common::str2int(classex[2]), classex[8], classex[9],classex[10]+", "+classex[11]);
			NewCourse->Add(*NewClass);
			delete NewClass;
			StartD=Date(0,0,0);
			EndD=Date(0,0,0);
		}
		Return->Add(*NewCourse);
		delete NewCourse;
		currentclass.clear();
		if (*lines==datastore.back()) {
			eof=false;
		}
	}
	table=*Return;
	delete Return;
	return true;
}

bool RabaskaDataStore::WriteTimetable(Timetable * TheTimetable){
	return false;
}
RabaskaDataStore::~RabaskaDataStore() {
}
