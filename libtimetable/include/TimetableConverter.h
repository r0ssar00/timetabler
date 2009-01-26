/*
 *  TimetableConverter.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
#ifndef _TIMETABLECONVERTER_H
#define _TIMETABLECONVERTER_H
#include "Timetable.h"
#include "DataStore.h"

class TimetableConverter {
public:
	bool WriteToStore(Timetable * TheTimetable, DataStore * TheStore);
	Timetable * ReadFromStore(DataStore * TheStore);
	
};

#endif	/* _TIMETABLECONVERTER_H */