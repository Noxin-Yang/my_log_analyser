#include "processLog.h"
#include "analysis/error_stats.h"
#include "analysis/window_analyzer.h"
#include "core/line_parser.h"
#include "core/path_resolver.h"
#include "core/time_parser.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int processlog(config* con) {
	string log_path = resolveLogPath(con->path);
	ifstream logfile(log_path);
	if (!logfile) {
		cerr << "Error opening log file: " << log_path << endl;
		return 1;
	}

	ofstream outfile;
	if (!con->output.empty()) {
		outfile.open(con->output);
		if (!outfile) {
			cerr << "Error opening output file" << endl;
			return 1;
		}
	}

	cout << "Processing log file..." << endl;
	if (con->print) {
		cout << "Requests with 5XX status codes:" << endl;
	}

	string line;
	map<string, Request> request_map;
	vector<LogEntry> window_vector;
	size_t max_window_size = 0;
	time_t window_start = 0;
	time_t window_end = 0;
	string window_start_str;
	string window_end_str;

	while (getline(logfile, line)) {
		LogEntry entry;
		string time_data = getTimeData(line);
		if (time_data.empty() || time_data.find(' ') == string::npos) {
			cerr << "WARNING: Invalid time data format, skipping: " << line << endl;
			continue;
		}

		entry.time = time_data.substr(0, time_data.find(' '));
		entry.time_zone = time_data.substr(time_data.find(' ') + 1);
		try {
			entry.timestruct = parseTime(entry.time, entry.time_zone);
		}
		catch (const exception& e) {
			cerr << "WARNING: Error parsing time, skipping: " << e.what() << " in line: " << line << endl;
			continue;
		}

		if (con->from && totimet(entry.timestruct) < con->from) {
			continue;
		}
		if (con->to && totimet(entry.timestruct) > con->to) {
			continue;
		}

		entry.request = getRequestData(line);
		if (entry.request.empty()) {
			cerr << "WARNING: Invalid request data format, skipping: " << line << endl;
			continue;
		}

		int is_5xx = calculate_5XX_status(request_map, entry, con, line);
		if (is_5xx && outfile.is_open()) {
			outfile << line << endl;
		}

		if (is_5xx && con->windows) {
			sliding_window(con, entry, max_window_size,
				window_vector, window_start, window_end,
				window_start_str, window_end_str);
		}
	}

	if (con->stats != 0) {
		vector<Request> requests;
		for (const auto& pair : request_map) {
			requests.emplace_back(pair.second);
		}
		sort(requests.begin(), requests.end(), [](const Request& a, const Request& b) {
			return a.req_count > b.req_count;
		});

		cout << endl << "==============================================================" << endl;
		cout << con->stats << " most frequent requests with status code 5XX by occurrencies:" << endl;
		cout << "<Number>. [<occurrencies>]\t<method> <path>\n" << endl;

		for (int i = 0; i < con->stats && i < requests.size(); ++i) {
			cout << i + 1 << ". [" << requests[i].req_count << "]\t" << requests[i].req_url << endl;
		}
	}

	if (con->windows) {
		cout << endl << "======================" << endl;
		cout << "Max window size: " << max_window_size << " requests in " << con->windows << " seconds." << endl;
		cout << "Start: " << window_start << ", " << window_start_str << endl;
		cout << "End:   " << window_end << ", " << window_end_str << endl;
	}

	return 0;
}
