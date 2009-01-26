/*
 *  DebugStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 23/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */

#ifndef _DEBUGDATASTORE_H
#define _DEBUGDATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class DebugDataStore : public DataStore {
public:
	DebugDataStore(int Kind);
	DebugDataStore(string FileName, int Kind, bool Piped = false);
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTable);
	bool IsReadOnly(){return false;};
	~DebugDataStore();
};
#endif