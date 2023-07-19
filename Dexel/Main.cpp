#include "Transpiler.h"
#include "FileUtils.h"
#include "Lexer.h"
#include "Parser.h"
#include "LexerTest.h"
#include "NumericValuesTest.h"
#include "StringUtilsTest.h"
#include "DatapackGenerator.h"

using namespace dexel;

void runTests() {
	LexerTest lexerTest;
	lexerTest.runTests();

	NumericValuesTest numericValuesTest;
	numericValuesTest.runTests();

	StringUtilsTest stringUtilsTest;
	stringUtilsTest.runTests();
}

int main(int argc, char** argv) {
	//runTests();

	Transpiler transpiler = Transpiler();
	transpiler.parseArguments(argc, argv);

	string sourceFilePath = transpiler.getSourceFile();
	string code = readFileToString(sourceFilePath);

	Lexer lexer(code, sourceFilePath);
	auto tokens = lexer.tokenize();

	SyntaxComponent::setGlobalSettings(transpiler.getDestinationDirectory(), transpiler.getOverrideDirectories());
	Parser parser(tokens, transpiler.getSourceFile());
	auto components = parser.parse();

	DatapackGenerator dg(transpiler.getDestinationDirectory(), transpiler.getOverrideDirectories());
	dg.generateDatapack(components);

	return 0;
}
