#ifndef DEXEL_TRANSPILER_H
#define DEXEL_TRANSPILER_H

#include <string>
#include <filesystem>

using namespace std;

namespace dexel {

	class Transpiler {

		string m_sourceFile = "";
		string m_destinationDirectory = filesystem::current_path().string();
		bool m_overrideDirectories = false;
		bool m_nativeCommands = false;

	public:
		int parseArguments(int argc, char** argv);

		inline const string& const getSourceFile() { return m_sourceFile; }
		inline const string& const getDestinationDirectory() { return m_destinationDirectory; }
		inline bool const getOverrideDirectories() { return m_overrideDirectories; }

	private:
		int printError(int errorCode);

	};
}

#endif
