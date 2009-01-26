/* 
 * File:   class.h
 * Author: r0ssar00
 *
 * Created on December 14, 2008, 10:16 PM
 */

#ifndef _CLASS_H
#define	_CLASS_H
using namespace std;
#include <list>
#include "../../include/Date.h"
#include "../../include/Common.h"
struct ClassData {
	string day;
	Date startday, endday;
    int recurrence, section;
    string type,location,room,instructor;
	Time start, end;
};

class Class {
public:
	Class();
	Class(string Encoded, bool Cal); //if you have the full course and class data from cal, pass true for Cal
    Class(string Day, Time Start, Time End, Date StartD, Date EndD, int Recurrence, string Type, int Section, string Location, string Room, string Instructor);
	string ToEncodedString();
	bool IsInited() {return clas.recurrence>=0;};
	Class& operator=(Class a);
	bool operator==(Class a);
	ClassData * GetData();
private:
	ClassData clas;
};

#endif	/* _CLASS_H */
