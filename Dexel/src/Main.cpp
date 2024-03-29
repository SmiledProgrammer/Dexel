#include "core/Transpiler.h"
#include "core/FileUtils.h"
#include "core/Lexer.h"
#include "core/Parser.h"
#include "test/LexerTest.h"
#include "test/NumericValuesTest.h"
#include "test/StringUtilsTest.h"
#include "core/DatapackGenerator.h"

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
#ifdef RUN_TESTS
	runTests();
#endif

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
