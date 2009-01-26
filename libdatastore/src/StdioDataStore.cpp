/*
 *  StdioDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 06/01/09.
 *  Copyright 2009 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include "../../libdatastore/include/StdioDataStore.h"

StdioDataStore::StdioDataStore(int Kind) {
	init = true;
}
StdioDataStore::StdioDataStore(string FileName, int Kind, bool Piped) {
	init = true;
	filename = FileName;
	pipe=Piped;
}
bool StdioDataStore::GetDataAsTimetable(int Year) {
	return true;
}
bool StdioDataStore::WriteTimetable(Timetable * TheTable) {
	return true;
}
StdioDataStore::~StdioDataStore() {
}
