#include"time_parser.h"
#include "log_types.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <algorithm>



//将当前的apache时间转换成unix时间戳并消除本地误差
time_t totimet(Time t) {
	long timezone_offset_sec = 0;
#ifdef _WIN32
	_get_timezone(&timezone_offset_sec);
#else
	timezone_offset_sec = timezone;
#endif
	time_t time = mktime(&t.timestruct) - timezone_offset_sec;
	return time - t.timezone_off_set;
}


Time parseTime(const string& date_time, const string& timezone) {
	Time t = {};
	//处理时区
	if (timezone.length() == 5) {
		int hour = stoi(timezone.substr(0, 3));
		int minute = stoi(timezone.substr(3, 2));
		t.timezone_off_set = hour * 3600 + minute * 60;
	}
	else {
		throw invalid_argument("Invalid timezone format");
	}

//处理apache时间
	istringstream ss(date_time);
	ss >> get_time(&t.timestruct, "%d/%b/%Y:%H:%M:%S");
	if (ss.fail()) {
		throw invalid_argument("Invalid datetime format" + date_time);
	}
	return t;
}