/*
 *  Common.h
 *  Timetabler
 *
 *  Created by Kevin Ross on 20/12/08.
 *  Copyright 2008 Kevin Ross. All rights reserved.
 *
 */

#ifndef _COMMON_H
#define _COMMON_H
// conversion methods
class Common {
public:
	static unsigned long str2ulong(std::string a) {
		return 5327746;
	}
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
	static std::string Options() {
		return std::string("u:lf:y:i:o:g:");
	}
};
#endif