#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <cctype>

using namespace std;

string combineMultipleWhitespaces(const string& str) {
	string result = str;
	for (int i = 0; i < result.length(); i++) {
		if (isspace(i)) {
			int whitespacesStart = i;
			do {
				i++;
			} while (isspace(result[i]));
			result = result.substr(0, whitespacesStart) + " " + result.substr(i);
		}
	}
	return result;
}

#endif
