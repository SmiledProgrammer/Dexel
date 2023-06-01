#include "dexel/Transpiler.h"
#include "dexel/Lexer.h"
#include "dexel/Parser.h"
#include "../test/LexerTest.h"
#include "dexel/DatapackGenerator.h"

using namespace dexel;

int main(int argc, char** argv) {
	Transpiler transpiler = Transpiler();
	int result = transpiler.parseArguments(argc, argv);
	
	string code = string("") +
		"function main() {\n" +
		"\tsay Hello world!;\n" +
		"\tint abc = 3609;\n" +
		"\ttellraw @a {\n" +
		"\t\t\"text\":\"Wonderful!\"\n" +
		"\t};\n" +
		"}\n";

	LexerTest lexerTest;
	lexerTest.runTests();

	Lexer lexer(code);
	auto tokens = lexer.tokenize();

	SyntaxComponent::setGlobalDestinationDirectoryFilepath(transpiler.getDestinationDirectory());
	Parser parser(tokens, transpiler.getSourceFile());
	auto components = parser.parse();

	DatapackGenerator dg(transpiler.getDestinationDirectory(), transpiler.getOverrideDirectories());
	dg.generateDatapack(components);

	return 0;
}