/*
 *  InfoWebDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */

#ifndef _INFOWEBDATASTORE_H
#define _INFOWEBDATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class InfoWebDataStore : public DataStore {
public:
	InfoWebDataStore(int Kind);
	InfoWebDataStore(string FileName, int Kind, bool Piped = false);
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTimetable);
	bool IsReadOnly(){return true;};
	~InfoWebDataStore();
};
#endif