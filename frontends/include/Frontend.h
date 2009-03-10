/*
 *  Frontend.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 19/12/08.
 *  Copyright 2008 Kevin Ross. All rights reserved.
 *
 */
#ifndef _FRONTEND_H
#define _FRONTEND_H
#include "../../libdatastore/include/DataStore.h"
#include "../../libtimetable/include/Timetable.h"
#define AERROR 1
#define AINFO 2
#define AWARN 3

class Frontend {
public:
	// the constructor brings up the initial user interface.  ie it inits the main window and sets up controls, but nothing else
	Frontend(){};
	// GetData prompts the user for a datastore and returns that datastore to the program
	virtual DataStore * GetData(int argc, char * const argv[]) = 0;
	// ReadData reads the data from the datastore's timetable and displays it on-screen
	virtual bool ReadData(DataStore * Data) = 0;
	// SaveData gets a datastore to save to
	virtual DataStore * SaveData(int argc, char * const argv[]) = 0;
	// Alert shows the user a message
	virtual void Alert(string Message, int Type=2)=0;
protected:
	Timetable * table;
	int year;
};
#endif
