/*
 *  DataStore.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 Kevin Ross. All rights reserved.
 *
 */
#ifndef _DATASTORE_H
#define _DATASTORE_H
using namespace std;
#include <list>
#include "../../libtimetable/include/Timetable.h"
#include "../../include/Date.h"
#define KIND_INPUT 1
#define KIND_OUTPUT 2
class DataStore {
public:
	DataStore(){};
	DataStore(int Kind){};
	DataStore(string FileName, int Kind, bool Piped = false){};
	virtual bool GetDataAsTimetable(int Year) = 0;
	virtual bool WriteTimetable(Timetable * TheTable) = 0;
	virtual bool IsReadOnly() = 0;
	bool ReadFile(string FileName) {
		ifstream input(FileName.c_str());
		string c;
		if (input.is_open()) {
			while (!input.eof() )
			{
				getline(input,c);
				datastore.push_back(c);
			}
			input.close();
		} else {
			return false;
		}
		return true;
	};
	bool IsInited(){return init;};
	Timetable * Table() {return &table;};
	void SetData(list<std::string> Data){
		datastore=Data;
	};
	list<std::string> * GetData() {
		return &datastore;
	};
	void SetTimetable(Timetable Table) {
		table=Table;
	};
	void SetPipe(bool Piped) {pipe=Piped;};
	bool GetPipe(){return pipe;};
	//virtual ~DataStore() = 0;
protected:
	StudentData SData;
	list<std::string> datastore;
	Timetable table;
	bool init;
	int kind;
	std::string filename;
	bool pipe;
};
#endif
