#include "../lib/processLog.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

int parseArgs(int argc, char** argv, config* config) {
	if (argc < 2) {
		cerr << "Usage: " << argv[0] << " [OPTIONS] logs_filename\n";
		return 1;
	}

	auto readValue = [&](int& i, const string& option) -> string {
		if (argc <= i + 1) {
			cerr << "Missing value for " << option << endl;
			return "";
		}
		return argv[++i];
	};

	for (int i = 1; i < argc; i++) {
		string arg = argv[i];
		if (arg == "--print" || arg == "-p") {
			config->print = true;
		}
		else if (arg.find("--output=") == 0) {
			config->output = arg.substr(9);
		}
		else if (arg == "--output" || arg == "-o") {
			string value = readValue(i, "--output");
			if (value.empty()) {
				return 1;
			}
			config->output = value;
		}
		else if (arg.find("--stats=") == 0) {
			string value = arg.substr(8);
			try {
				config->stats = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid stats value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "Stats value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg == "--stats" || arg == "-s") {
			string value = readValue(i, "--stats");
			if (value.empty()) {
				return 1;
			}
			try {
				config->stats = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid stats value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "Stats value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg.find("--window=") == 0) {
			string value = arg.substr(9);
			try {
				config->windows = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid window value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "Window value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg == "--window" || arg == "-w") {
			string value = readValue(i, "--window");
			if (value.empty()) {
				return 1;
			}
			try {
				config->windows = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid window value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "Window value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg.find("--from=") == 0) {
			string value = arg.substr(7);
			try {
				config->from = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid from value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "From value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg == "--from" || arg == "-f") {
			string value = readValue(i, "--from");
			if (value.empty()) {
				return 1;
			}
			try {
				config->from = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid from value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "From value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg.find("--to=") == 0) {
			string value = arg.substr(5);
			try {
				config->to = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid to value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "To value out of range: " << value << endl;
				return 1;
			}
		}
		else if (arg == "--to" || arg == "-e") {
			string value = readValue(i, "--to");
			if (value.empty()) {
				return 1;
			}
			try {
				config->to = stoll(value);
			}
			catch (invalid_argument) {
				cerr << "Invalid to value: " << value << endl;
				return 1;
			}
			catch (out_of_range) {
				cerr << "To value out of range: " << value << endl;
				return 1;
			}
		}
		else if (config->path.empty() && arg[0] != '-') {
			config->path = arg;
		}
		else {
			cerr << "Unknown option: " << arg << endl;
			return 1;
		}
	}

	if (config->path.empty()) {
		cerr << "Missing path to log file" << endl;
		return 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	config con;
	if (parseArgs(argc, argv, &con) != 0) {
		return 1;
	}
	if (processlog(&con) != 0) {
		return 1;
	}
	return 0;
}
