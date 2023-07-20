#include "StringUtils.h"

string removeNewlines(const string& str) {
	string result = str;
	for (int i = 0; i < result.length(); i++) {
		if (result[i] == '\n') {
			while (i < result.length() && isspace(result[i])) {
				result = result.substr(0, i) + result.substr(i + 1);
			}
		}
	}
	return result;
}
