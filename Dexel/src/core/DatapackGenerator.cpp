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
	generateEmptyDatapack();
	generateDefaultInitFunction();
	generateMCFunctionFiles(components);
}

void DatapackGenerator::generateEmptyDatapack() {
	string functionsPathStr = "\\" + DEXEL_DATAPACK_NAME + "\\data\\" + DEXEL_DATAPACK_NAMESPACE + "\\functions";
	string absoluteFunctionsPathStr = m_destinationDirectory + functionsPathStr;
	if (m_overrideDirectories || !fs::is_directory(fs::path(absoluteFunctionsPathStr))) {
		fs::current_path(fs::path(m_destinationDirectory));
		fs::create_directories("." + functionsPathStr);
	}
	string absoluteMetaPathStr = m_destinationDirectory + "\\" + DEXEL_DATAPACK_NAME + "\\pack.mcmeta";
	if (m_overrideDirectories || !fs::is_regular_file(fs::path(absoluteMetaPathStr))) {
		createPackMCMetaFile(absoluteMetaPathStr);
	}
}

void DatapackGenerator::generateDefaultInitFunction() {
	string initFunctionPath = m_destinationDirectory + "\\" + DEXEL_DATAPACK_NAME + "\\data\\" + DEXEL_DATAPACK_NAMESPACE + "\\functions\\dexel-init.mcfunction";
	ofstream initFunctionStream(initFunctionPath);
	initFunctionStream << "scoreboard objectives add dexel_vars dummy" << endl;
	initFunctionStream << "scoreboard objectives add dexel_helpers dummy" << endl;
	initFunctionStream << "scoreboard players set .condition_met_counter dexel_helpers 0" << endl;
	initFunctionStream.close();

	string functionConfigurationDirectoryPath = "\\" + DEXEL_DATAPACK_NAME + "\\data\\minecraft\\tags\\functions";
	string absoluteFunctionConfigurationDirectoryPath = m_destinationDirectory + functionConfigurationDirectoryPath;
	if (m_overrideDirectories || !fs::is_directory(fs::path(absoluteFunctionConfigurationDirectoryPath))) {
		fs::current_path(fs::path(m_destinationDirectory));
		fs::create_directories("." + functionConfigurationDirectoryPath);
	}

	string loadConfigurationPath = absoluteFunctionConfigurationDirectoryPath + "\\load.json";
	ofstream loadConfigurationStream(loadConfigurationPath);
	loadConfigurationStream << "{" << endl;
	loadConfigurationStream << TAB << "\"values\": [" << endl;
	loadConfigurationStream << TAB << TAB << "\"dexel:dexel-init\"" << endl;
	loadConfigurationStream << TAB << "]" << endl;
	loadConfigurationStream << "}" << endl;
	loadConfigurationStream.close();
}

void DatapackGenerator::generateMCFunctionFiles(const vector<DexelFileSyntaxComponent>& components) {
	for (DexelFileSyntaxComponent dexelFile : components) {
		string filepath = dexelFile.getFilepath();
		dexelFile.convertToMCFunctionCode(filepath);
	}
}

void DatapackGenerator::createPackMCMetaFile(const string& pathStr) {
	ofstream fileStream(pathStr);
	fileStream << "{" << endl;
	fileStream << TAB << "\"pack\": {" << endl;
	fileStream << TAB << TAB << "\"pack_format\": 10," << endl;
	fileStream << TAB << TAB << "\"description\": \"Datapack created with Dexel language\"" << endl;
	fileStream << TAB << "}" << endl;
	fileStream << "}" << endl;
	fileStream.close();
}
