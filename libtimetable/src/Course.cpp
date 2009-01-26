/* 
 * File:   course.cpp
 * Author: r0ssar00
 * 
 * Created on December 14, 2008, 10:15 PM
 */
using namespace std;
#include <pme.h>
#include "../../libtimetable/include/Course.h"
#include "../../include/Date.h"
void TrimSpaces( string& str)  {  
	// Code for Trim trailing Spaces only 
	size_t endpos = str.find_last_not_of(" \t"); // Find the first character position from reverse af 
	if( string::npos != endpos ) 
		str = str.substr( 0, endpos+1 ); 
}  
Class ClassComp;
Course::Course() {
}
Course::Course(string Name, string Code, string Section) {
    course.name=Name;
    course.code=Code;
	course.section=Section;
	TrimSpaces(course.section);
}
void Course::Add(Class::Class NewClass) {
	Class cp = NewClass;
    classes.push_back(cp);
}
bool do_remove(const Class& AClass) {
    return ClassComp==AClass;
}
bool Course::Remove(Class::Class OldClass) {
    ClassComp=OldClass;
	list<Class>::iterator i;
	for (i = classes.begin(); i!= classes.end(); ++i) {
		if (*i==OldClass) {
			break;
		}
	}
	if (i != classes.end()) {
		classes.remove_if(do_remove);
		return true;
	} else {
		return false;
	}
	return false;
}

bool Course::Modify(Class::Class OldClass, Class NewClass) {
	ClassComp=OldClass;
	list<Class>::iterator i;
	for (i = classes.begin(); i!= classes.end(); ++i) {
		if (*i==OldClass) {
			break;
		}
	}
	if (i != classes.end()) {
		for (i = classes.begin(); i!= classes.end(); ++i) {
			if (*i==OldClass) {
				*i=NewClass;
			}
		}
		return true;
	} else {
		return false;
	}
	
}
list<Class> * Course::Get(){
    return &classes;
}
CourseData Course::GetData() {
	return course;
}
void Course::SetYear(int Year) {
	// go through each class and set the year
	list<Class>::iterator i;
	for (i=classes.begin(); i!=classes.end(); i++) {
		i->GetData()->startday.year=Year;
		i->GetData()->endday.year=Year;
	}
}
string Course::ToEncodedString() {
	string Output="";
	Output+="$"+course.code+"$"+course.section+"$"+course.name+"$";
	return Output;
}

Course::Course(string Encoded, bool Cal) {
	// $code$section$name$
	// 1=code, 2=section, 3=name
	if (Cal) {
		Encoded=Encoded.substr(1,Encoded.find_first_of("\\N"));
	}
	course=GetEncodedData(Encoded);
}
CourseData Course::GetEncodedData(string Encoded) {
	CourseData T;
	string encre = "\\$([A-Z][A-Z][A-Z][0-9][0-9][0-9][0-9])\\$([A-Z ]*)\\$([^$]*)\\$";
	PME encex(encre.c_str(),"");
	if (encex.match(Encoded)==0) {
		T.code="";
	}
	T.name=encex[3];
	T.code=encex[1];
	T.section=encex[2];
	return T;
}	
Course& Course::operator=(Course a) {
	classes.clear();
	list<Class> ac = *(a.Get());
	list<Class>::iterator i;
	for (i=ac.begin(); i!=ac.end(); i++) {
		classes.push_back(*i);
	}
	return *this;
}
bool Course::operator==(Course a) {
	list<Class> ac = *(a.Get());
	bool classesequal = equal(classes.begin(),classes.end(),ac.begin());
	bool nameequal = course.name==a.GetData().name;
	bool codeequal = course.code==a.GetData().code;
	bool sectionequal = course.section==a.GetData().section;
	return (classesequal==nameequal==codeequal==sectionequal==true);
}
