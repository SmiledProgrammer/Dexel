#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <cctype>

using namespace std;

string combineMultipleWhitespaces(const string& str) {
	// TODO: ignore string literals in commands ("" or '') - but actually don't ignore newlines (\n)
	string result = str;
	for (int i = 0; i < result.length(); i++) {
		if (isspace(str[i])) {
			int whitespacesStart = i;
			do {
				i++;
			} while (isspace(result[i]));
			result = result.substr(0, whitespacesStart) + " " + result.substr(i);
		}
	}
	return result;
}

string cutDexelExtensionFromFilepath(const string& str) {
	if (str.ends_with(".dexel")) {
		return str.substr(0, str.length() - 6);
	}
	return str;
}

#endif
