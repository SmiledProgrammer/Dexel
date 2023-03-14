#include "Transpiler.h"

#include "Lexer.h"
#include "LanguageConstants.h"

using namespace dexel;

#include <map>
#include <iostream>
using namespace std;

template<typename K, typename V>
static map<V, K> reverse_map(const map<K, V>& m) {
	map<V, K> r;
	for (const auto& kv : m)
		r[kv.second] = kv.first;
	return r;
}

const map<Token::Type, string> tokenTypeNames{
			{Token::TYPE_COMMAND, "Command"},
			{Token::TYPE_IDENTIFIER, "Identifier"},
			{Token::TYPE_FUNCTION_KEYWORD, "Keyword function"},
			{Token::TYPE_IF_KEYWORD, "Keyword if"},
			{Token::TYPE_ELSE_KEYWORD, "Keyword else"},
			{Token::TYPE_INT_KEYWORD, "Keyword int"},
			{Token::TYPE_INTEGER_LITERAL, "Integer literal"},
			{Token::TYPE_EQUALS_OPERATOR, "Equals"},
			{Token::TYPE_PLUS_OPERATOR, "Plus"},
			{Token::TYPE_HYPHEN_OPERATOR, "Hyphen"},
			{Token::TYPE_ASTERISK_OPERATOR, "Asterisk"},
			{Token::TYPE_FORWARD_SLASH_OPERATOR, "Forward slash"},
			{Token::TYPE_SEMICOLON_SEPARATOR, "Semicolon"},
			{Token::TYPE_LEFT_PARENTHESES_SEPARATOR, "Left parentheses"},
			{Token::TYPE_RIGHT_PARENTHESES_SEPARATOR, "Right parentheses"},
			{Token::TYPE_LEFT_BRACES_SEPARATOR, "Left braces"},
			{Token::TYPE_RIGHT_BRACES_SEPARATOR, "Right braces"},
			{Token::TYPE_HASH_COMMENT, "Hash"}
};

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
	map<Token::Type, char> reverseOfSymbolTokens = reverse_map(SYMBOL_TOKENS);
	for (Token token : tokens) {
		auto tokenChar = reverseOfSymbolTokens.find(token.getType());
		if (tokenChar != reverseOfSymbolTokens.end()) {
			cout << tokenTypeNames.find(token.getType())->second << ": " << tokenChar->second << endl;
		} else {
			cout << tokenTypeNames.find(token.getType())->second << ": " << token.getValue() << endl;
		}
	}

	return 0;
}
