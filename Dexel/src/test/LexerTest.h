﻿#ifndef LEXER_TEST_H
#define LEXER_TEST_H

#include <string>
#include "../core/Lexer.h"

using namespace std;

namespace dexel {

	/**
	 * \brief Klasa testów analizy składniowej.
	 *
	 * Klasa testowa do przeprowadzania testów analizy składniowej.
	 */
	class LexerTest {
	public:
		struct TestCase {
			string code;
			vector<Token> expectedTokens;

			TestCase(const string& code, vector<Token> expectedTokens)
				: code(code), expectedTokens(expectedTokens) {}
		};

	private:
		vector<TestCase> m_testCases;

	public:
		LexerTest();

		int runTests();

	private:
		void displayFailInfo(const vector<Token>& expectedTokens, const vector<Token>& actualTokens);
		void displayTokenVector(const vector<Token>& tokens);
		Token createToken(Token::Type type, const string& value = "");

	};
}

#endif
