using namespace std;
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <pme.h>
#include "../frontends/include/Frontend.h"
// compile-time front-end configuration
// terminal always included
#include "../frontends/include/TerminalFrontend.h"
void ListUi();
int main (int argc, char * const argv[]) {
	// process ui command line argument
	int opt;
	string ui;
	while ((opt=getopt(argc,argv,Common::Options().c_str())) != -1) {
		switch (opt) {
			case 'u':
				ui=string(optarg);
				break;
			case 'l':
				ListUi();
				return 0;
				break;
			case 'f':
				break;
			case 'y':
				break;
			case 'i':
				break;
			case 'o':
				break;
			case 'g':
				break;
			default:
				cout << "Usage: " << argv[0] << " [-l] [-u UserInterface]" <<endl;
				cout << "-l Lists the available frontends and datasources\n-u Chooses from the frontends" <<endl;
				break;
		}
	}
	Frontend * Display;
	DataStore * Input;
	DataStore * Output;
	string Filename;
	if (ui=="Terminal") {
		Display = new TerminalFrontend();
	} else {
		Display = new TerminalFrontend();
	}
	Input = Display->GetData(argc, argv);
	if (!Input->IsInited()) {
		Display->Alert("Could not initalize input data store!",AERROR);
		return 2;
	}
	Output = Display->SaveData(argc, argv);
	if (!Output->IsInited()) {
		Display->Alert("Could not initalize output data store!",AERROR);
		return 2;
	}
	if (!Display->ReadData(Input)) {
		Display->Alert("Could not display or read data!",AERROR);
		return 2;
	}
	Output->WriteTimetable(Input->Table());
    return 0;
}
void ListUi() {
	cout << "User Interfaces compiled into this version are: " << endl;
	cout << "	Terminal" << endl << "	Cocoa" << endl;
	cout << "Input/Output modules compiled into this version are: " <<endl;
	cout << "	InfoWeb(Input only)" << endl << "	Debug(Output only)\n	iCal(Input and Output)\n" <<endl;
}