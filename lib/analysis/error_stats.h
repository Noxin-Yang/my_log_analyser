#pragma once

#include "../core/log_types.h"
#include "../core/line_parser.h"
#include "../processLog.h"

#include <map>
#include <string>

using namespace std;

int calculate_5XX_status(map<string, Request>& request_map, LogEntry& entry, config* config, const string& line);


