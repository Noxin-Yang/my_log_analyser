#pragma once
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
using namespace std;


// 从一行日志里提取 time/request/status


//从文件中摘出时间
string getTimeData(const string& str);

//从文件里摘出请求
string getRequestData(const string& str);

//从文件中摘出状态码
string getStatusCode(const string& str);
