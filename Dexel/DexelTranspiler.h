#ifndef DEXEL_TRANSPILER_H
#define DEXEL_TRANSPILER_H

#include <string>
#include <filesystem>

using namespace std;

class DexelTranspiler {
	string m_sourceFile = "";
	string m_destinationDirectory = filesystem::current_path().string();
	bool m_overrideDirectories = false;
	bool m_nativeCommands = false;

public:
	int parseArguments(int argc, char** argv);

};

#endif
