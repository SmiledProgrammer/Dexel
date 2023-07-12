#include "LexerTest.h"

#include <iostream>
#include "LanguageConstants.h"

using namespace dexel;
using namespace std;

const map<Token::Type, string> tokenTypeNames{
			{Token::TYPE_UNKNOWN_SYMBOL, "Unknown symbol"},
			{Token::TYPE_COMMAND, "Command"},
			{Token::TYPE_CONDITION, "Condition"},
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

template<typename K, typename V>
std::map<V, K> reverseMap(const std::map<K, V>& m) {
	std::map<V, K> r;
	for (const auto& kv : m)
		r[kv.second] = kv.first;
	return r;
}

map<Token::Type, char> reverseOfSymbolTokens = reverseMap(SYMBOL_TOKENS);


LexerTest::LexerTest() {
	TestCase multilineCommandTest = TestCase(
		string("\ttellraw @a {\n") +
			"\t\t\"text\":\"Wonderful!\"\n" +
			"\t};\n"
		,
		{
			Token(Token::TYPE_COMMAND, "tellraw @a {\"text\":\"Wonderful!\"}"),
			Token(Token::TYPE_SEMICOLON_SEPARATOR)
		}
	);

	TestCase allTokensTest = TestCase(
		string("function main() {\n") +
		"\tsay Hello world!;\n" +
		"\tint abc = 3609;\n" +
		"\ttellraw @a {\n" +
		"\t\t\"text\":\"Wonderful!\"\n" +
		"\t};\n" +
		"\tint def = abc + 2 * 3 - 8 / 7;\n" +
		"\tif (score dexel_vars def = 5) {\n" +
		"\t\tsay Incorrect.;\n" +
		"\t} else {\n" +
		"\t\tsay Very bad.;\n" +
		"\t}\n"
		"}\n"
		,
		{
			Token(Token::TYPE_FUNCTION_KEYWORD),
			Token(Token::TYPE_IDENTIFIER, "main"),
			Token(Token::TYPE_LEFT_PARENTHESES_SEPARATOR),
			Token(Token::TYPE_RIGHT_PARENTHESES_SEPARATOR),
			Token(Token::TYPE_LEFT_BRACES_SEPARATOR),

			Token(Token::TYPE_COMMAND, "say Hello world!"),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_INT_KEYWORD),
			Token(Token::TYPE_IDENTIFIER, "abc"),
			Token(Token::TYPE_EQUALS_OPERATOR),
			Token(Token::TYPE_INTEGER_LITERAL, "3609"),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_COMMAND, "tellraw @a {\"text\":\"Wonderful!\"}"),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_INT_KEYWORD),
			Token(Token::TYPE_IDENTIFIER, "def"),
			Token(Token::TYPE_EQUALS_OPERATOR),
			Token(Token::TYPE_IDENTIFIER, "abc"),
			Token(Token::TYPE_PLUS_OPERATOR),
			Token(Token::TYPE_INTEGER_LITERAL, "2"),
			Token(Token::TYPE_ASTERISK_OPERATOR),
			Token(Token::TYPE_INTEGER_LITERAL, "3"),
			Token(Token::TYPE_HYPHEN_OPERATOR),
			Token(Token::TYPE_INTEGER_LITERAL, "8"),
			Token(Token::TYPE_FORWARD_SLASH_OPERATOR),
			Token(Token::TYPE_INTEGER_LITERAL, "7"),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_IF_KEYWORD),
			Token(Token::TYPE_LEFT_PARENTHESES_SEPARATOR),
			Token(Token::TYPE_CONDITION, "score dexel_vars def = 5"),
			Token(Token::TYPE_RIGHT_PARENTHESES_SEPARATOR),
			Token(Token::TYPE_LEFT_BRACES_SEPARATOR),

			Token(Token::TYPE_COMMAND, "say Incorrect."),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_RIGHT_BRACES_SEPARATOR),
			Token(Token::TYPE_ELSE_KEYWORD),
			Token(Token::TYPE_LEFT_BRACES_SEPARATOR),

			Token(Token::TYPE_COMMAND, "say Very bad."),
			Token(Token::TYPE_SEMICOLON_SEPARATOR),

			Token(Token::TYPE_RIGHT_BRACES_SEPARATOR),

			Token(Token::TYPE_RIGHT_BRACES_SEPARATOR)
		}
	);

	m_testCases = {
		multilineCommandTest,
		allTokensTest
	};
}

int LexerTest::runTests() {
	int failedTestsCount = 0;
	for (TestCase testCase : m_testCases) {
		vector<Token> expectedTokens = testCase.expectedTokens;
		Lexer lexer(testCase.code);
		vector<Token> actualTokens = lexer.tokenize();
		if (expectedTokens != actualTokens) {
			failedTestsCount++;
			displayFailInfo(expectedTokens, actualTokens);
		}
	}
	cout << "Lexer tests run. Failed tests count: " << failedTestsCount << endl;
	return failedTestsCount;
}

void LexerTest::displayFailInfo(const vector<Token>& expectedTokens, const vector<Token>& actualTokens) {
	cout << "Test failed - expected tokens:" << endl;
	displayTokenVector(expectedTokens);
	cout << "but actually got:" << endl;
	displayTokenVector(actualTokens);
	cout << endl;
}

void LexerTest::displayTokenVector(const vector<Token>& tokens) {
	for (Token token : tokens) {
		auto tokenChar = reverseOfSymbolTokens.find(token.getType());
		if (tokenChar != reverseOfSymbolTokens.end()) {
			cout << "    " << tokenTypeNames.find(token.getType())->second << ": " << tokenChar->second << endl;
		}
		else {
			cout << "    " << tokenTypeNames.find(token.getType())->second << ": " << token.getValue() << endl;
		}
	}
}
