/* 
 * File:   timetable.h
 * Author: r0ssar00
 *
 * Created on December 14, 2008, 10:13 PM
 */

#ifndef _TIMETABLE_H
#define	_TIMETABLE_H
using namespace std;
#include <list>
#include "../../libtimetable/include/Course.h"
#include "../../include/Date.h"
#include "../../include/Common.h"
struct TimetableData {
	Date start, end;
	int year;
	string name, program;
	unsigned long number;
};
class StudentData {
public:
	StudentData(){name="";number=0;program="";year=0;filename="";};
	StudentData(string Name, unsigned long Number, string Program, int Year, string Filename, char Filet){name=Name;number=Number;program=Program;year=Year;filename=Filename;filet=Filet;};
	string name;
	unsigned long number;
	string program;
	int year;
	string filename;
	char filet;
};
class Timetable {
public:
	Timetable() {};
    Timetable(Date Start,Date End);
	Timetable(int Year);
	void Add(Course NewCourse);
	Course * Add(string EncodedString);
	bool Modify(Course OldCourse, Course NewCourse);
	bool Remove(Course OldCourse);
	Course * Find(CourseData TheCourse);
	list<Course> * Get();
	TimetableData GetData();
	void SetData(TimetableData t){table=t;};
	void SetYear(int Year);
	void FixDates();
private:
	TimetableData table;
	list<Course> courses;
};

#endif	/* _TIMETABLE_H */

