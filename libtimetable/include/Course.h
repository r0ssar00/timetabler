/* 
 * File:   course.h
 * Author: r0ssar00
 *
 * Created on December 14, 2008, 10:15 PM
 */

#ifndef _COURSE_H
#define	_COURSE_H
using namespace std;
#include <list>
#include "../../libtimetable/include/Class.h"
#include "../../include/Date.h"
#include "../../include/Common.h"
struct CourseData {
	string name, code, section;
};
class Course {
public:
	Course();
	Course(string Encoded, bool Cal); //if you have the full course and class data from cal, pass true for Cal
    Course(string Name, string Code, string Section);
    void Add(Class NewClass);
	Course * Add(string EncodedString);
    bool Modify(Class OldClass, Class NewClass);
    bool Remove(Class OldClass);
	Class * Find(string EncodedString);
    list<Class> * Get();
	CourseData GetEncodedData(string Encoded);
	CourseData GetData();
	void SetData(CourseData c){course=c;};
	void SetYear(int Year);
	string ToEncodedString();
	bool IsInited() {return course.code!="";};
	Course& operator=(Course a);
	bool operator==(Course a);
private:
    CourseData course;
    list<Class> classes;
};

#endif	/* _COURSE_H */

