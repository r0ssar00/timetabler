/* 
 * File:   course.cpp
 * Author: r0ssar00
 * 
 * Created on December 14, 2008, 10:15 PM
 */
using namespace std;
#include "../../libtimetable/include/Timetable.h"
#include "../../include/Date.h"
Course CourseComp;
Timetable::Timetable(int Year) {
	table.year=Year;
}
Timetable::Timetable(Date Start, Date End) {
	table.start=Start;
	table.end=End;
}
void Timetable::Add(Course NewCourse) {
	courses.push_back(NewCourse);
}
bool do_remove(const Course& ACourse) {
    return CourseComp==ACourse;
}
bool Timetable::Remove(Course::Course OldCourse) {
    CourseComp=OldCourse;
	list<Course>::iterator i;
	for (i = courses.begin(); i!= courses.end(); ++i) {
		if (*i==OldCourse) {
			break;
		}
	}
	if (i != courses.end()) {
		courses.remove_if(do_remove);
		return true;
	} else {
		return false;
	}
	return false;
}

bool Timetable::Modify(Course::Course OldCourse, Course NewCourse) {
	CourseComp=OldCourse;
	list<Course>::iterator i;
	for (i = courses.begin(); i!= courses.end(); ++i) {
		if (*i==OldCourse) {
			break;
		}
	}
	if (i != courses.end()) {
		for (i = courses.begin(); i!= courses.end(); ++i) {
			if (*i==OldCourse) {
				*i=NewCourse;
			}
		}
		return true;
	} else {
		return false;
	}
	
}

list<Course> * Timetable::Get() {
	return & courses;
}

TimetableData Timetable::GetData() {
	return table;
}
void Timetable::SetYear(int Year) {
	// go through each class and set the year
	list<Course>::iterator i;
	for (i=courses.begin(); i!=courses.end(); i++) {
		i->SetYear(Year);
	}
}
void Timetable::FixDates() {
	list<Course>::iterator i;
	list<Class>::iterator j;
	list<Class> * k;
	Date StartD;
	for(i=courses.begin(); i!=courses.end(); i++) {
		k=i->Get();
		for(j=k->begin(); j!=k->end(); j++) {
			StartD = j->GetData()->startday;
			StartD = Date::GetNearestDay(StartD,j->GetData()->day);
			j->GetData()->startday=StartD;
		}
	}
}
