#pragma once

#include <ctime>
#include <cstring>
#include <string>

using namespace std;

class Request {
public:
	string req_url;
	int req_count;

	Request(const string& req_url) : req_url(req_url), req_count(1) {}
};

class Time {
public:
	tm timestruct;
	int timezone_off_set;

	Time() {
		timezone_off_set = 0;
		memset(&timestruct, 0, sizeof(tm));
	}
};

class LogEntry {
public:
	string time;
	string time_zone;
	Time timestruct;
	string request;
	string status;
};
