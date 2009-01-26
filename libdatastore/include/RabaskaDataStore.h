/*
 *  RabaskaDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 07/01/09.
 *  Copyright 2009 uOttawa. All rights reserved.
 *
 */

#ifndef _RABASKADATASTORE_H
#define _RABASKADATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class RabaskaDataStore : public DataStore {
public:
	RabaskaDataStore(int Kind);
	RabaskaDataStore(string FileName, int Kind, bool Piped = false);
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTimetable);
	bool IsReadOnly(){return true;};
	~RabaskaDataStore();
};
#endif