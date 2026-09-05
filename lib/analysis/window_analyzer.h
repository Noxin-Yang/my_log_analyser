#pragma once

#include "../core/log_types.h"
#include "../core/line_parser.h"
#include "../processLog.h"

#include <ctime>
#include <string>
#include <vector>

void sliding_window(config* config, LogEntry& entry, size_t& max_window_size,
	vector<LogEntry>& window_vector, time_t& win_start,
	time_t& win_end, string& win_st_str, string& win_ed_str);
