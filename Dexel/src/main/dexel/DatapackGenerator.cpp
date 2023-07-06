#include "DatapackGenerator.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include "StringUtils.h"
#include "LanguageConstants.h"

using namespace dexel;
using namespace std;
namespace fs = filesystem;

const string TAB = "\t";

DatapackGenerator::DatapackGenerator(const string& destinationDirectory, bool overrideDirectories)
	: m_destinationDirectory(destinationDirectory), m_overrideDirectories(overrideDirectories) {}

void DatapackGenerator::generateDatapack(const vector<DexelFileSyntaxComponent>& components) {
	generateEmptyDatapack("DexelDatapack");
	generateMCFunctionFiles(components);
}

void DatapackGenerator::generateEmptyDatapack(const string& datapackName) {
	string functionsPathStr = "\\" + datapackName + "\\data\\" + DEXEL_DATAPACK_NAMESPACE + "\\functions";
	string absoluteFunctionsPathStr = m_destinationDirectory + functionsPathStr;
	if (fs::is_directory(fs::path(absoluteFunctionsPathStr))) {
		cout << "[WARN] Functions directory already exists and will not be overriden." << endl;
	} else {
		fs::current_path(fs::path(m_destinationDirectory));
		fs::create_directories("." + functionsPathStr);
	}
	string absoluteMetaPathStr = m_destinationDirectory + "\\" + datapackName + "\\pack.mcmeta";
	if (fs::is_regular_file(fs::path(absoluteMetaPathStr))) {
		cout << "[WARN] pack.mcmeta file already exists and will not be overriden." << endl;
	} else {
		createPackMCMetaFile(absoluteMetaPathStr);
	}
}

void DatapackGenerator::generateMCFunctionFiles(const vector<DexelFileSyntaxComponent>& components) {
	for (DexelFileSyntaxComponent dexelFile : components) {
		string filepath = dexelFile.getFilepath();
		for (SyntaxComponent component : dexelFile.getComponents()) {
			//string callingCode = component.convertToMCFunctionCode();
			// TODO: move this
			/*string generatedFilepath = cutDexelExtensionFromFilepath(sourceFilepath) + "-" + component->getFunctionIdentifier() + ".mcfunction";
			ofstream fileStream(generatedFilepath);
			fileStream << component->convertToMCFunctionCode() << endl;
			fileStream.close();*/
		}
	}
}

void DatapackGenerator::createPackMCMetaFile(const string& pathStr) {
	ofstream fileStream(pathStr);
	fileStream << "{" << endl;
	fileStream << TAB << "\"pack\": {" << endl;
	fileStream << TAB << TAB << "\"pack_format\": 10," << endl;
	fileStream << TAB << TAB << "\"description\": \"Datapack created with Dexel language\"," << endl;
	fileStream << TAB << "}" << endl;
	fileStream << "}" << endl;
	fileStream.close();
}
