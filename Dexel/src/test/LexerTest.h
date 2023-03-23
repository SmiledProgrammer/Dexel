#ifndef LEXER_TEST_H
#define LEXER_TEST_H

#include <list>
#include <string>
#include "../main/dexel/Lexer.h"


using namespace std;

namespace dexel {

	class LexerTest {
	public:
		struct TestCase {
			string code;
			list<Token> expectedTokens;

			TestCase(const string& code, list<Token> expectedTokens)
				: code(code), expectedTokens(expectedTokens) {}
		};

		list<TestCase> m_testCases;

	public:
		LexerTest();

		int runTests();

	private:
		void displayFailInfo(const list<Token>& expectedTokens, const list<Token>& actualTokens);
		void displayTokenList(const list<Token>& tokens);

	};
}

#endif
