#include "window_analyzer.h"
#include "../core/time_parser.h"

using namespace std;

void sliding_window(config* config, LogEntry& entry, size_t& max_window_size,
	vector<LogEntry>& window_vector, time_t& win_start,
	time_t& win_end, string& win_st_str, string& win_ed_str)
{
	window_vector.emplace_back(entry);

	while (!window_vector.empty() &&
		totimet(entry.timestruct) - totimet(window_vector.front().timestruct) + 1 > config->windows) {
		window_vector.erase(window_vector.begin());
	}

	if (window_vector.size() > max_window_size) {
		max_window_size = window_vector.size();
		win_start = totimet(window_vector.front().timestruct);
		win_st_str = window_vector.front().time + " " + window_vector.front().time_zone;
		win_end = totimet(window_vector.back().timestruct);
		win_ed_str = window_vector.back().time + " " + window_vector.back().time_zone;
	}
}

