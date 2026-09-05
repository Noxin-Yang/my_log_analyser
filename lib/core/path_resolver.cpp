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
#include <system_error>
#include <filesystem>
#include"path_resolver.h"
using namespace std;
string resolveLogPath(const string& path) {
	filesystem::path requested(path);
	error_code  error;
	if (requested.is_absolute() || filesystem::exists(requested)) {
		return requested.string();
	}
	filesystem::path current = filesystem::current_path(error);
	if (error) {
		return requested.string();
	}
	while (true) {
		filesystem::path candidate = current / path;
		error.clear();
		if (filesystem::is_regular_file(candidate, error)) {
			return candidate.string();
		}
		if (!current.has_parent_path() || current == current.parent_path()) {
			break;
		}
		current = current.parent_path();
	}
	return requested.string();
}