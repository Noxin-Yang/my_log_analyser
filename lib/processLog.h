#pragma once

#include <string>

using namespace std;

class config {
public:
	string path;
	string output;
	bool print;
	long long stats;
	long long windows;
	long long from;
	long long to;

	config() : print(false), stats(10), windows(0), from(0), to(0) {}
};

int processlog(config* con);
