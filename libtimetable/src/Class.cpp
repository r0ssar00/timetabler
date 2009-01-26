/* 
 * File:   course.cpp
 * Author: r0ssar00
 * 
 * Created on December 14, 2008, 10:15 PM
 */
using namespace std;
#include <cctype> // for toupper
#include <algorithm>
#include <pme.h>
#include "../../libtimetable/include/Class.h"
#include "../../include/Date.h"
Class::Class() {
	clas.day="";
	clas.start=Time(0,0);
	clas.end=Time(0,0);
	clas.startday=Date(0,0,0);
	clas.endday=Date(0,0,0);
	clas.recurrence=-1;
	clas.section=0;
	clas.location="";
	clas.room="";
	clas.type="";
	clas.instructor="";
}
Class::Class(string Day, Time Start, Time End, Date StartD, Date EndD, int Recurrence, string Type, int Section, string Location, string Room, string Instructor) {
    clas.day=Day;
	transform(clas.day.begin(), clas.day.end(), clas.day.begin(), (int(*)(int)) toupper);
    clas.start=Start;
    clas.end=End;
	clas.startday=StartD;
	clas.endday=EndD;
    clas.recurrence=Recurrence;
    clas.section=Section;
    clas.location=Location;
	clas.room=Room;
	clas.instructor=Instructor;
    clas.type=Type;
}
string Class::ToEncodedString() {
	string Output="";
	Output+="$"+clas.day+"$"+Date::GetRfcTime(&(clas.startday), &(clas.start))+"$"+Date::GetRfcTime(&(clas.endday), &(clas.end));
	Output+="$"+Common::int2str(clas.recurrence);
	Output+="$"+Common::int2str(clas.section)+"$"+clas.location+"$";
	Output+=clas.room+"$"+clas.instructor+"$"+clas.type+"$";
	return Output;
}
Class::Class(string Encoded, bool Cal) {
	if (Cal) {
		Encoded=Encoded.substr(Encoded.find_first_of("\\N"+3),Encoded.length());
	}
	// $DAY$startdayTstarttime$enddayTendtime$recurrence$section$location$room$instructor$type$
	// 1=day, 2=startday, 3=starttime, 4=endday, 5=endtime, 6=recurrence, 7=section, 8=location, 9=room, 10=instructor, 11=type
	string encre = "\\$([A-Z]*)\\$([0-9])T([0-9])\\$([0-0])T([0-9])\\$([0-9])\\$([0-9])\\$([^$])\\$([^$])\\$([^$])\\$([^$])\\$";
	PME encex(encre.c_str(),"");
	if (encex.match(Encoded)==0) {
		clas.recurrence=-1;
	}
	clas.day=encex[1];
    clas.start=Time::FromRfc(encex[3]);
    clas.end=Time::FromRfc(encex[5]);
	clas.startday=Date::FromRfc(encex[2]);
	clas.endday=Date::FromRfc(encex[4]);
    clas.recurrence=Common::str2int(encex[6]);
    clas.section=Common::str2int(encex[7]);
    clas.location=encex[8];
	clas.room=encex[9];
	clas.instructor=encex[10];
    clas.type=encex[11];
}
ClassData * Class::GetData() {
	return &clas;
}
Class& Class::operator=(Class a) {
	clas.day=a.GetData()->day;
	clas.start=a.GetData()->start;
	clas.end=a.GetData()->end;
	clas.startday=a.GetData()->startday;
	clas.endday=a.GetData()->endday;
	clas.recurrence=a.GetData()->recurrence;
	clas.section=a.GetData()->section;
	clas.location=a.GetData()->location;
	clas.room=a.GetData()->room;
	clas.instructor=a.GetData()->instructor;
	clas.type=a.GetData()->type;
	return *this;
}
bool Class::operator==(Class AClass) {
	if (clas.day!=AClass.GetData()->day) {
		return false;
	}
	if (!((clas.start.hour==AClass.GetData()->start.hour)&&(clas.start.minute==AClass.GetData()->start.minute))) {
		return false;
	}
	if (!((clas.end.hour==AClass.GetData()->end.hour)&&(clas.end.minute==AClass.GetData()->end.minute))) {
		return false;
	}
	if (clas.recurrence!=AClass.GetData()->recurrence) {
		return false;
	}
	if (clas.section!=AClass.GetData()->section) {
		return false;
	}
	if (clas.location!=AClass.GetData()->location) {
		return false;
	}
	if (clas.instructor!=AClass.GetData()->instructor) {
		return false;
	}
	if (clas.type!=AClass.GetData()->type) {
		return false;
	}
	return true;
}

