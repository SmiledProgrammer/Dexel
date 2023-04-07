#include "Transpiler.h"

#include <iostream>
#include <map>

using namespace dexel;

const map<int, string> ERROR_CODES{
	{-1, "Selected destination is not a directory."},
	{-2, "Selected source file is not a Dexel language file."},
	{-3, "Selected source is not a file."},
	{-4, "After -src or -dst option you must specify the directory path."},
	{-5, "Unknown program option."},
	{-6, "Source file must be provided (\"-src\" option)."}
};

int Transpiler::parseArguments(int argc, char** argv) {
	int optionsCount = 0;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-native") == 0) {
			m_nativeCommands = true;
		} else if (strcmp(argv[i], "-override") == 0) {
			m_overrideDirectories = true;
		} else if (strcmp(argv[i], "-src") == 0 || strcmp(argv[i], "-dst") == 0) {
			if (++i < argc) {
				string pathStr = argv[i];
				if (strcmp(argv[i - 1], "-dst") == 0) {
					if (filesystem::is_directory(filesystem::path(pathStr))) {
						m_destinationDirectory = pathStr;
					} else {
						return printError(-1);
					}
				} else {
					if (filesystem::is_regular_file(filesystem::path(pathStr))) {
						if (pathStr.ends_with(".dexel")) {
							m_sourceFile = pathStr;
						} else {
							return printError(-2);
						}
					} else {
						return printError(-3);
					}
				}
			} else {
				return printError(-4);
			}
		} else {
			return printError(-5);
		}
		optionsCount++;
	}
	if (m_sourceFile == "") {
		return printError(-6);
	}
	cout << "Loaded " << optionsCount << " transpilation options correctly." << endl;
	return optionsCount;
}

int Transpiler::printError(int errorCode) {
	auto mapPos = ERROR_CODES.find(errorCode);
	if (mapPos == ERROR_CODES.end()) {
		cerr << "[ERROR] Unexpected error occurred." << endl;
		return -418;
	}
	string errorMsg = mapPos->second;
	cerr << "[ERROR] " << errorMsg << endl;
	return errorCode;
}
