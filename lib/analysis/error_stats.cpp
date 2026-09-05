#include "error_stats.h"

#include <iostream>
#include <stdexcept>

using namespace std;

int calculate_5XX_status(map<string, Request>& request_map, LogEntry& entry, config* config, const string& line) {
	entry.status = getStatusCode(line);
	try {
		int status_int = stoi(entry.status);
		if (entry.status.empty() || status_int < 100 || status_int > 599) {
			throw invalid_argument("Invalid status code format");
		}
	}
	catch (const exception&) {
		cerr << "WARNING: Invalid status code format, skipping " << endl;
		return 0;
	}

	if (entry.status[0] == '5') {
		if (config->print) {
			cout << line << endl;
		}
		if (config->stats) {
			auto result = request_map.emplace(entry.request, Request(entry.request));
			if (!result.second) {
				result.first->second.req_count++;
			}
		}
		return 1;
	}

	return 0;
}


