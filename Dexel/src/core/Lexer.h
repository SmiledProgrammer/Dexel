#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

namespace dexel {

	/**
	 * \brief Klasa analizy składniowej.
	 *
	 * Klasa służąca do przeprowadzania analizy składniowej kodu języka Dexel.
	 */
	class Lexer {
	
		string m_code;
		string m_sourceCodeFilepath;
		int m_position;
		int m_line, m_column;
		char m_currentChar;
		vector<Token> m_tokens;

	public:
		Lexer(const string& code, const string& sourceCodeFilepath);

		/**
		 * \brief Funkcja analizy składniowej.
		 *
		 * Funkcja służąca do przeprowadzenia analizy składniowej.
		 *
		 * \return Lista tokenów języka Dexel.
		 */
		vector<Token> tokenize();

	private:
		void advance();
		void processComment();
		void processSymbol(Token::Type symbolTokenType);
		void processInteger();
		void processExpression();
		void processCommand(string& expression);
		void processCondition(string& expression);
		void processDexelKeyword(Token::Type keywordTokenType, const string& keyword);
		void processIdentifier(const string& identifier);

		bool isIdentifierCharacter(char c);
		Token createToken(Token::Type type, const string& value = "");

	};
}

#endif
