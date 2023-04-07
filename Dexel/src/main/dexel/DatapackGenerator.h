#ifndef DATAPACK_GENERATOR_H
#define DATAPACK_GENERATOR_H

#include <string>

using namespace std;

namespace dexel {

	class DatapackGenerator {

		string m_destinationDirectory;
		bool m_overrideDirectories;

	public:
		DatapackGenerator(const string& destinationDirectory, bool overrideDirectories);

		void generateDatapack(/* TODO: list<SyntaxStructure> */);

	private:
		void generateEmptyDatapack(const string& datapackName);
		void generateMCFunctionFiles(/* TODO: list<SyntaxStructure> */);

		void createPackMCMetaFile(const string& pathStr);

	};
}

#endif
