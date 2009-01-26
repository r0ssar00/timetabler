/*
 *  StdioDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 06/01/09.
 *  Copyright 2009 uOttawa. All rights reserved.
 *
 */

#ifndef _STDIODATASTORE_H
#define _STDIODATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class StdioDataStore : public DataStore {
public:
	StdioDataStore(int Kind);
	StdioDataStore(string FileName, int Kind, bool Piped = false);
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTable);
	bool IsReadOnly(){return false;};
	~StdioDataStore();
};
#endif