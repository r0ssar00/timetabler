/*
 *  XmlDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include "../../libdatastore/include/XmlDataStore.h"

bool XmlDataStore::GetDataAsTimetable(int Year) {
	return &Timetable();
}

bool XmlDataStore::WriteTimetable(Timetable * TheTable) {
	return false;
}
