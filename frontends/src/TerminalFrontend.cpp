/*
 *  terminal.cpp
 *  Timetabler
 *
 *  Created by Kevin Ross on 19/12/08.
 *  Copyright 2008 uOttawa. All rights reserved.
 *
 */
using namespace std;
#include <ctime>
#include <list>
#include "../../frontends/include/TerminalFrontend.h"
#include "../../libtimetable/include/Timetable.h"
TerminalFrontend::TerminalFrontend() {};
void usage(char * const argv[]);

DataStore * TerminalFrontend::GetData(int argc, char * const argv[]) {
	// parse the command-line args
	DataStore * ThisStore;
	options.inputf="";
	options.inputd="";
	options.outputf="";
	options.outputd="";
	options.year=0;
	string u;
	int opt=0;
	// reset optind to 1 so getopt will work again
	optind=1;
	while ((opt=getopt(argc,argv,Common::Options().c_str())) != -1) {
		switch (opt) {
			case 'f':
				options.inputf=string(optarg);
				break;
			case 'y':
				options.year=Common::str2int(optarg);
				break;
			case 'i':
				options.inputd=string(optarg);
				break;
			case 'u':
				break;
			case 'h':
				usage(argv);
				return ThisStore;
				break;
			case 'o':
				options.outputd=string(optarg);
				break;
			case 'g':
				options.outputf=string(optarg);
				break;
			default:
				usage(argv);
				return ThisStore;
				break;
		}
	}
	if (options.inputf=="") {
		options.inputf="Input.txt";
	}
	if (options.outputf=="") {
		options.outputf="Output.ics";
	}
	if (options.outputd=="") {
		options.outputd="File";
	}
	if (options.year==0) {
		time_t t;
		time(&t);
		struct tm *pt =localtime(&t);
		if (pt) {
			options.year=pt->tm_year+1900;
		}
	}
	// new datastore template:
	/*
	 else if (options.inputd=="UniqueNameOfStore") {
		ThisStore = new NameOfDataStore(options.inputf, KIND_INPUT);
	 }
	 */
	if (options.inputd=="InfoWeb" || options.inputd=="") {
		ThisStore = new InfoWebDataStore(options.inputf, KIND_INPUT);
	} else if (options.inputd=="Rabaska") {
		ThisStore = new RabaskaDataStore(options.inputf, KIND_INPUT);
	}
	return ThisStore;
}
bool TerminalFrontend::ReadData(DataStore * Data) {
	// Data has already been initialized, get the timetable
	if (!Data->GetDataAsTimetable(options.year)) {
		return false;
	}
	table=Data->Table();
	// if it didn't add any courses, Data failed to get it's data
	if (table->Get()->size()==0) {
		return false;
	} else {
		return true;
	}
}

DataStore * TerminalFrontend::SaveData(int argc, char * const argv[]) {
	DataStore * ThisStore;
	if (options.outputd=="Debug") {
		ThisStore = new DebugDataStore(options.outputf, KIND_OUTPUT);
	} else if (options.outputd=="iCal") {
		ThisStore = new FileDataStore(options.outputf, KIND_OUTPUT);
	}
	return ThisStore;
}

void TerminalFrontend::Alert(string Message, int Type) {
	string t = "";
	if (Type==1) {
		t="Terminal: ERROR: ";
	} else if (Type==2) {
		t="Terminal: Info: ";
	} else if (Type==3) {
		t="Terminal: Warning: ";
	}
	cout << t << Message << endl;
}
void usage(char * const argv[]) {
	cout << "Terminal: Usage: " << argv[0] << " -u Terminal  [-i InputStore] [-f Input FileName] [-y Year] [-o OutputStore] [-g Output FileName]" <<endl;
	cout << "Terminal:	-i: If given, the input type to use.  Defaults to InfoWeb." <<endl;
	cout << "Terminal:	-f: If given, the filename to read from.  Defaults to Input.txt in the current directory." <<endl;
	cout << "Terminal:	-y: If given, the year to generate the timetable for.  Defaults to the current year." <<endl;
	cout << "Terminal:	-o: If given, the output type to use.  Defaults to iCalendar(File)." <<endl;
	cout << "Terminal:	-g: If given, the filename to write to.  Defaults to Output.cal in the current directory." <<endl;
}
