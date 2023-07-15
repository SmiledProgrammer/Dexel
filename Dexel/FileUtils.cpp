#include "FileUtils.h"

#include <fstream>
#include <sstream>

string readFileToString(const string& absolutePath) {
	ifstream fileStream(absolutePath);
	stringstream buffer;
	buffer << fileStream.rdbuf();
	return buffer.str();
}
