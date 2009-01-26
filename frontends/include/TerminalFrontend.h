/*
 *  terminal.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 19/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
#ifndef _TERMINALFRONTEND_H
#define _TERMINALFRONTEND_H
#include "../../frontends/include/Frontend.h"
#include "../../include/Common.h"
#include "../../libtimetable/include/Timetable.h"
#include "../../libdatastore/include/InfoWebDataStore.h"
#include "../../libdatastore/include/DebugDataStore.h"
#include "../../libdatastore/include/FileDataStore.h"
#include "../../libdatastore/include/RabaskaDataStore.h"
struct optionsst {
	string inputf, outputf;
	string inputd, outputd;
	int year;
};
class TerminalFrontend : public Frontend {
public:
	TerminalFrontend();
	DataStore * GetData(int argc, char * const argv[]);
	bool ReadData(DataStore * Data);
	DataStore * SaveData(int argc, char * const argv[]);
	void Alert(string Message, int Type=2);
private:
	optionsst options;
};
#endif
