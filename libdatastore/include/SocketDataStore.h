/*
 *  SocketDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */

#ifndef _SOCKETDATASTORE_H
#define _SOCKETDATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class SocketDataStore : public DataStore {
public:
	SocketDataStore();
	SocketDataStore(string FileName):DataStore(FileName){};
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTable);
	bool IsReadOnly(){return false;};
};
#endif