/*
 *  Date.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 16/12/08.
 *  Copyright 2008 Kevin Ross. All rights reserved.
 *
 */
#ifndef _DATE_H
#define _DATE_H
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include "../include/Common.h"
class Time {
public:
	int hour;
	int minute;
	Time() {
		hour=0;
		minute=0;
	}
	Time(int Hour, int Minute) {
		hour=Hour;
		minute=Minute;
	}
	Time(std::string Hour, std::string Minute) {
		hour=str2int(Hour);
		minute=str2int(Minute);
	}
	void Set(int Hour, int Minute) {
		hour=Hour;
		minute=Minute;
	}
	bool operator==(Time & a) {
		if (hour==a.hour && minute==a.minute) {
			return true;
		} else {
			return false;
		}
	}
	static std::string Format(Time * t) {
		return padto2(t->hour)+":"+padto2(t->minute);
	}
	std::string Get12Hr() {
		std::string suf;
		int nhour = hour;
		if (nhour > 12) {
			nhour-=12;
			suf="pm";
		} else if (nhour==0 || nhour==24) {
			nhour=12;
			suf="am";
		} else {
			suf="am";
		}
		
		return int2str(nhour)+":"+padto2(minute)+suf;
	}
	static Time FromRfc(std::string RfcTime) {
		// hhmmss
		return Time(RfcTime.substr(0,2),RfcTime.substr(2,2));
	}
private:
	static int str2int(std::string str) {
		return std::atoi(str.c_str());
	}
	static std::string int2str(int a) {
		std::string o = "";
		char b[4];
		sprintf(b,"%d",a);
		o+=b;
		return o;
	}
	static std::string padto2(int a) {
		if (a<10) {
			return "0"+int2str(a);
		} else {
			return int2str(a);
		}
	}
};

class Date {
public:
	int day;
	int month;
	int year;
	Date() {
		day=0;
		month=0;
		year=0;
	}
	Date(int Day, int Month, int Year) {
		day=Day;
		month=Month;
		year=Year;
	}
	void Set(int Day, int Month, int Year) {
		day=Day;
		month=Month;
		year=Year;
	}
	bool operator==(Date & a) {
		if (day==a.day && month==a.month && year==a.year) {
			return true;
		} else {
			return false;
		}
	}
	static std::string Format(Date * d) {
		return Common::padto2(d->day)+"."+Common::padto2(d->month)+"."+Common::int2str(d->year);
	}
	static std::string GetRfcTime(Date * day, Time * time) {
		// YYYYMMDDTHHMMSS
		std::string out;
		out=Common::int2str(day->year);
		out=out+Common::padto2(day->month);
		out=out+Common::padto2(day->day);
		out=out+"T";
		out=out+Common::padto2(time->hour);
		out=out+Common::padto2(time->minute);
		out=out+"00";
		return out;
	}
	static std::string ToString(Date * d) {
		return std::string(MonthNameFromInt(d->month) + std::string(" ") + Common::int2str(d->day) + std::string(", ") + Common::int2str(d->year));
	}
	// this takes a day(say Jan 6, the start of class), and returns the next matching day of week
	// eg: startday=Jan 6, dayofweek=Monday.  this will return the day number in Jan that matches the first monday occuring after Jan 6
	static Date Date::GetNearestDay(Date startday, int dayofweek) {
		int startWday = DayOfWeek(startday.day,startday.month, startday.year);
		// assume never near the end of the month(for now)
		Date newstart;
		newstart.day=startday.day;
		newstart.month=startday.month;
		newstart.year=startday.year;
		if (dayofweek > startWday) {
			newstart.day=newstart.day+(dayofweek-startWday);
		} else if (dayofweek < startWday){
			// go to the next week
			newstart.day+=7;
			newstart.day=newstart.day-(startWday-dayofweek);
		}
		return newstart;
	}
	static Date Date::GetNearestDay(Date startday, std::string sdayofweek) {
		return GetNearestDay(startday, DayFromName(sdayofweek));
	}
	static std::string ThreeLetterDayToFullName(std::string day) {
		return DayNameFromInt(DayFromName(day));
	}
	static std::string DayNameFromInt(int day) {
		if (day==0) {
			return std::string("Sunday");
		} else if (day==1) {
			return std::string("Monday");
		} else if (day==2) {
			return std::string("Tuesday");
		} else if (day==3) {
			return std::string("Wednesday");
		} else if (day==4) {
			return std::string("Thursday");
		} else if (day==5) {
			return std::string("Friday");
		} else if (day==6) {
			return std::string("Saturday");
		} else {
			return std::string("Huh?");
		}
	}
	static std::string MonthNameFromInt(int month) {
		if (month==1) {
			return std::string("Jan");
		} else if (month==2) {
			return std::string("Feb");
		} else if (month==3) {
			return std::string("Mar");
		} else if (month==4) {
			return std::string("Apr");
		} else if (month==5) {
			return std::string("May");
		} else if (month==6) {
			return std::string("Jun");
		} else if (month==7) {
			return std::string("Jul");
		} else if (month==8) {
			return std::string("Aug");
		} else if (month==9) {
			return std::string("Sep");
		} else if (month==10) {
			return std::string("Oct");
		} else if (month==11) {
			return std::string("Nov");
		} else if (month==12) {
			return std::string("Dec");
		} else {
			return std::string("Huh?");
		}
	}
	static int DayFromName(std::string day) {
		std::string sday = day.substr(0,2);
		if (sday=="Su" || sday=="SU") {
			return 0;
		} else if (sday=="Mo" || sday=="MO") {
			return 1;
		} else if (sday=="Tu" || sday=="TU") {
			return 2;
		} else if (sday=="We" || sday=="WE") {
			return 3;
		} else if (sday=="Th" || sday=="TH") {
			return 4;
		} else if (sday=="Fr" || sday=="FR") {
			return 5;
		} else if (sday=="Sa" || sday=="SA") {
			return 6;
		} else {
			return -1;
		}
	}
	static int MonthFromName(std::string mon) {
		if (mon=="Jan") {
			return 1;
		} else if (mon=="Feb") {
			return 2;
		} else if (mon=="Mar") {
			return 3;
		} else if (mon=="Apr") {
			return 4;
		} else if (mon=="May") {
			return 5;
		} else if (mon=="Jun") {
			return 6;
		} else if (mon=="Jul") {
			return 7;
		} else if (mon=="Aug") {
			return 8;
		} else if (mon=="Sep") {
			return 9;
		} else if (mon=="Oct") {
			return 10;
		} else if (mon=="Nov") {
			return 11;
		} else if (mon=="Dec") {
			return 12;
		} else {
			return 0;
		}
	}
	static Date FromRfc(std::string RfcDate) {
		//yyyymmdd
		return Date(Common::str2int(RfcDate.substr(6,8)),Common::str2int(RfcDate.substr(4,6)),Common::str2int(RfcDate.substr(0,4)));
	}
private:
	static int		DayOfWeek( int nDay, int nMonth, int nYear )
	{
		int			nDayOfWeek;
		const static int	pnDaysBeforeMonth[] = {
			0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
		};
		
		assert( nMonth > 0 && nMonth <= 12 );
		assert( nDay > 0 );
		assert( nDay <= ( pnDaysBeforeMonth[ nMonth+1 ] - pnDaysBeforeMonth[ nMonth ] )
			   || ( nMonth == 2 && nDay == 29 && IsLeapYear(nYear) )
			   );
		
		/* the day of Jan 1, nYear */
		nDayOfWeek = 6 + nYear % 7 + CountOfFeb29(nYear) % 7 + 14;/* + 14 : makes nDayOfWeek >= 0 */
		
		/* the day of nMonth 1, nYear */
		nDayOfWeek += pnDaysBeforeMonth[ nMonth ];
		if( nMonth > 2 && IsLeapYear(nYear) )	nDayOfWeek++;
		
		/* the day of nMonth nDay, nYear */
		nDayOfWeek += nDay - 1;
		nDayOfWeek %= 7;
		
		return nDayOfWeek;
	}
	
	/*
	 *	Count of days, which is Feb 29, from Jan 1, 0 to Jan 1, nYear
	 *	There is no Feb 29 between Jan 1, 0 and Jan 1, -3, one between Jan 1, 0 and Jan 1, -4
	 *	one between Jan 1, 0 and Jan 1, 3 AD, one between Jan 1, 0 and Jan 1, 4
	 */
	static int		CountOfFeb29( int nYear )
	{
		int		nCount = 0;
		if( nYear > 0 ) {
			nCount = 1;	/* Year 0 is a leap year */
			nYear--;/* Year nYear is not in the period */
		}
		nCount += nYear / 4 - nYear / 100 + nYear / 400;
		
		return nCount;
	}
	
	static bool	IsLeapYear( int nYear )
	{
		if( nYear % 4 != 0 )	return false;
		if( nYear % 100 != 0 )	return true;
		return ( nYear % 400 == 0 );
	}
	
	static int str2int(std::string str) {
		return std::atoi(str.c_str());
	}
};

#endif
