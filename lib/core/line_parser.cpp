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
#include"line_parser.h"
using namespace std;

string getTimeData(const string& str) {
	auto start = str.find('[');
	auto end = str.find(']');
	if (start == string::npos || end == string::npos) {
		return "";
	}
	return str.substr(start+1, end - start - 1);

}

string getRequestData(const string& str) {
	auto start = str.find('\"');
	auto end = str.rfind('\"');
	if (start == string::npos || end == string::npos) {
		return "";
	}
	return str.substr(start+1, end - start - 1);
}


string getStatusCode(const string& str) {
	auto end = str.rfind(' ');
	if (end == string::npos || end == 0) {
		return "";
	}
	auto start = str.rfind(' ', end - 1);
	if (start == std::string::npos || start + 1 >= end) {
		return "";
	}
	return str.substr(start + 1, end - start - 1);
}
