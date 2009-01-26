/*
 *  DebugDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 23/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include "../../libdatastore/include/DebugDataStore.h"

DebugDataStore::DebugDataStore(int Kind){init=true;}
DebugDataStore::DebugDataStore(string FileName, int Kind, bool Piped){init=true;pipe=Piped;}
bool DebugDataStore::GetDataAsTimetable(int Year){return true;}
bool DebugDataStore::WriteTimetable(Timetable * TheTable) {
	// the only method really needed for the debug store
	// the debug store outputs the data to console only
	cout << "Timetable:" << endl;
	list<Course>::iterator i;
	list<Class>::iterator j;
	list<Course> * courses;
	list<Class> * classes;
	courses=TheTable->Get();
	for (i=courses->begin(); i!=courses->end(); i++) {
		classes=i->Get();
		cout << "	" << i->GetData().code << "  " << i->GetData().section << "  " << i->GetData().name << endl;
		for (j=classes->begin(); j!=classes->end(); j++) {
			/*
			 string day;
			 Date startday, endday;
			 int recurrence, section;
			 string type,location,room,instructor;
			 Time start, end;
			 */
			cout << "		***********************************"<<endl;
			cout << "		A " <<j->GetData()->type<< " on "<< j->GetData()->day << "s at " << j->GetData()->start.Get12Hr() << " until " << j->GetData()->end.Get12Hr() << endl;
			cout << "		First day of class: " << j->GetData()->day << " " << Date::ToString(&(j->GetData()->startday)) << "  Last occurs around " << Date::ToString(&(j->GetData()->endday)) <<endl;
			cout << "		Section: " <<j->GetData()->section<<endl<<"		Recurrence: "<<j->GetData()->recurrence<<endl;
			cout << "		Building: " <<j->GetData()->location<<"  Room: "<<j->GetData()->room<<endl<<"		Prof: "<<j->GetData()->instructor<<endl;
		}
	}
	return true;
}
DebugDataStore::~DebugDataStore() {
}