#ifndef DATAPACK_GENERATOR_H
#define DATAPACK_GENERATOR_H

#include <string>
#include "DexelFileSyntaxComponent.h"

using namespace std;

namespace dexel {

	class DatapackGenerator {

		string m_destinationDirectory;
		bool m_overrideDirectories;

	public:
		DatapackGenerator(const string& destinationDirectory, bool overrideDirectories);

		void generateDatapack(const vector<DexelFileSyntaxComponent>& components);

	private:
		void generateEmptyDatapack(const string& datapackName);
		void generateMCFunctionFiles(const vector<DexelFileSyntaxComponent>& components);

		void createPackMCMetaFile(const string& pathStr);

	};
}

#endif
