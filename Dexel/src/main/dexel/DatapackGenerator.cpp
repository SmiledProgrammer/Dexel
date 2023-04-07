#include "DatapackGenerator.h"

#include <filesystem>
#include <iostream>
#include <fstream>

using namespace dexel;
using namespace std;
namespace fs = filesystem;

const string FUNCTIONS_NAMESPACE = "dexel";

DatapackGenerator::DatapackGenerator(const string& destinationDirectory, bool overrideDirectories)
	: m_destinationDirectory(destinationDirectory), m_overrideDirectories(overrideDirectories) {}

void DatapackGenerator::generateDatapack(/* TODO: list<SyntaxStructure> */) {
	generateEmptyDatapack("DexelDatapack");
	generateMCFunctionFiles();
}

void DatapackGenerator::generateEmptyDatapack(const string& datapackName) {
	string functionsPathStr = "\\" + datapackName + "\\data\\" + FUNCTIONS_NAMESPACE + "\\functions";
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

void DatapackGenerator::generateMCFunctionFiles(/* TODO: list<SyntaxStructure> */) {
	// TODO
}

void DatapackGenerator::createPackMCMetaFile(const string& pathStr) {
	ofstream fileStream(pathStr);
	fileStream << "{" << endl;
	fileStream << "\t\"pack\": {" << endl;
	fileStream << "\t\t\"pack_format\": 10," << endl;
	fileStream << "\t\t\"description\": \"Datapack created with Dexel language\"," << endl;
	fileStream << "\t}" << endl;
	fileStream << "}" << endl;
	fileStream.close();
}
