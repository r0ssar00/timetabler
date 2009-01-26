/*
 *  InfoWebDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <pme.h>
#include "../../libdatastore/include/InfoWebDataStore.h"
InfoWebDataStore::InfoWebDataStore(int Kind) {
	kind=KIND_INPUT;
	init=true;
}
InfoWebDataStore::InfoWebDataStore(string FileName, int Kind, bool Piped){
	kind=KIND_INPUT;
	datastore.clear();
	pipe=Piped;
	if (!pipe) {
		init=ReadFile(FileName);
	}
}
bool comp(string first, string second) {
	int f,s;
	f=Date::DayFromName(first);
	s=Date::DayFromName(second);
	if (f<s) {
		return true;
	} else {
		return false;
	}
}
bool InfoWebDataStore::GetDataAsTimetable(int Year){
	// headerre has backrefs 1-7
	string headerre = "([A-Z][A-Z][A-Z][0-9][0-9][0-9][0-9]) " // course code
						"([A-Z][A-Z]? )?" // section
						"([A-Z0-9 ]*) " // name
						"\\(([A-Z][a-z][a-z]) ([0-9][0-9]?) - ([A-Z][a-z][a-z]) ([0-9][0-9]?)\\)"; //date
	// profre has backrefs 1-2
	string profre =  "Prof: ([^,]*), (.*)"; // prof
	// classre has backrefs 1-10
	string classre = "([A-Za-z]*) \t" // day
					 "([A-Z]{3})(\\((\\d)\\))? \t" // Type, optional section
					 "(\\d\\d):(\\d\\d)-(\\d\\d):(\\d\\d) \t" //time
					 "[^_]*\\(([A-Z][A-Z][A-Z])\\) \t" // location
					 "Room: ([A-Za-z0-9]*)"; // room
	PME headerex(headerre.c_str(),"");
	PME profex(profre.c_str(),"");
	PME classex(classre.c_str(),"");
	string currentcourse = "";
	string currentprof = "";
	list<string> currentclass;
	list<string>::iterator lines = datastore.begin();
	bool eof = true;
	Timetable * Return = new Timetable(Year);
	while (eof) {
		currentcourse=*lines;
		lines++;
		currentprof=*lines;
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
		// doesn't match infoweb format, return empty timetable
		if (headerex.match(currentcourse)==0||profex.match(currentprof)==0||currentclass.size()==0) {
			return false;
		}
		// sort by day of week
		currentclass.sort(comp);
		Date StartD, EndD, iStartD,iEndD;
		iStartD = Date(Common::str2int(headerex[5]),Date::MonthFromName(headerex[4]),Year);
		iEndD =  Date(Common::str2int(headerex[7]),Date::MonthFromName(headerex[6]),Year);
		Course * NewCourse = new Course(headerex[3],headerex[1],headerex[2]);
		Class * NewClass;
		list<string>::iterator curclass;
		for (curclass=currentclass.begin(); curclass!=currentclass.end(); curclass++) {
			classex.match(*curclass);
			StartD=Date::GetNearestDay(iStartD,classex[1]);
			EndD=iEndD;
			NewClass = new Class(classex[1], Time(classex[5],classex[6]), Time(classex[7],classex[8]),StartD,EndD,1, classex[2], (classex[4]!="")? Common::str2int(classex[4]):0,classex[9],classex[10], profex[1] + ", " + profex[2]);
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

bool InfoWebDataStore::WriteTimetable(Timetable * TheTimetable){
	return false;
}
InfoWebDataStore::~InfoWebDataStore() {
}