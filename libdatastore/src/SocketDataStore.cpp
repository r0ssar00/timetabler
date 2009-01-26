/*
 *  MacDataStore.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 * 
 *  Will probably have to communicate with an Obj-C program through a socket or something.  Looks
 *  like c++ can't use CalendarStore directly.
 */

using namespace std;
#include "../../libdatastore/include/SocketDataStore.h"


bool SocketDataStore::GetDataAsTimetable(int Year) {
	return &Timetable();
}

bool SocketDataStore::WriteTimetable(Timetable * TheTable) {
	return false;
}
