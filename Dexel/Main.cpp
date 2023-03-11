#include "Transpiler.h"
#include "Lexer.h"

using namespace dexel;

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	Transpiler transpiler = Transpiler();
	int result = transpiler.parseArguments(argc, argv);
	
	string code = string("function main() {\n") +
						 "\t  say Hello world!;\n" +
						 "\t  int abc = 3609;\n" +
						 "\t  tellraw @a {\n" +
						 "\t\t    \"text\":\"Wonderful!\"\n" +
						 "\t  };\n" +
						 "\t  int def = abc + 2 * 3 - 8 / 7;\n" +
						 "}\n";

	Lexer lexer(code);
	list<Token> tokens = lexer.tokenize();
	for (Token token : tokens) {
		cout << token.getType() << ": " << token.getValue() << "," << endl;
	}

	return 0;
}
