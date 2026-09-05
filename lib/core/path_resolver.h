
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

// 日志路径解析
string resolveLogPath(const string& path);
