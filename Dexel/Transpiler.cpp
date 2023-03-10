#include "Transpiler.h"

#include <iostream>
#include <string>

using namespace dexel;

int Transpiler::parseArguments(int argc, char** argv) {
	int optionsCount = 0;
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-native") == 0) {
			m_nativeCommands = true;
		} else if (strcmp(argv[i], "-override") == 0) {
			m_overrideDirectories = true;
		} else if (strcmp(argv[i], "-src") == 0 || strcmp(argv[i], "-dst") == 0) {
			if (++i < argc) {
				string path = argv[i];
				if (strcmp(argv[i - 1], "-dst") == 0) {
					m_destinationDirectory = path;
				} else {
					if (path.ends_with(".dexel")) {
						m_sourceFile = path;
					} else {
						cerr << "Selected source file is not a Dexel language file." << endl;
						return -1;
					}
				}
			} else {
				cerr << "After -src or -dst option you must specify the directory path." << endl;
				return -1;
			}
		} else {
			cerr << "Unknown program option \"" << argv[i] << "\"." << endl;
			return -1;
		}
		optionsCount++;
	}
	if (m_sourceFile == "") {
		cerr << "Source file must be provided (\"-src\" option)." << endl;
		return -1;
	}
	cout << "Loaded " << optionsCount << " transpilation options correctly." << endl;
	return optionsCount;
}
