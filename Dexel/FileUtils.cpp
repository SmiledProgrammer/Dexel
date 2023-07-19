#include "FileUtils.h"

#include <fstream>
#include <sstream>
#include "LanguageConstants.h"

using namespace dexel;

string readFileToString(const string& absolutePath) {
	ifstream fileStream(absolutePath);
	stringstream buffer;
	buffer << fileStream.rdbuf();
	return buffer.str();
}
