/*
 *  TimetableConverter.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include "../include/TimetableConverter.h"

bool TimetableConverter::WriteToStore(Timetable * TheTimetable, DataStore * TheStore) {
	if (!TheStore->IsReadOnly()) {
		return TheStore->WriteTimetable(TheTimetable);
	} else {
		return false;
	}
}
Timetable * TimetableConverter::ReadFromStore(DataStore * TheStore) {
	return new Timetable(Date(0,0,0),Date(0,0,0));
}