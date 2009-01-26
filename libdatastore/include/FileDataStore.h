/*
 *  FileDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */

#ifndef _FILEDATASTORE_H
#define _FILEDATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class FileDataStore : public DataStore {
public:
	FileDataStore(int Kind);
	FileDataStore(string FileName, int Kind, bool Piped = false);
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTimetable);
	bool IsReadOnly(){return false;};
	~FileDataStore();
private:
	string MakeLineLength(string Input);
};
#endif