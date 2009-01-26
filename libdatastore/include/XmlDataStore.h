/*
 *  XmlDataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */

#ifndef _XMLDATASTORE_H
#define _XMLDATASTORE_H
#include "../../libdatastore/include/DataStore.h"

class XmlDataStore : public DataStore {
public:
	XmlDataStore();
	XmlDataStore(string FileName):DataStore(FileName){};
	bool GetDataAsTimetable(int Year);
	bool WriteTimetable(Timetable * TheTimetable);
	bool IsReadOnly(){return false;};
};
#endif