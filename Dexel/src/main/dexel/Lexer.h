#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "Token.h"

using namespace std;

namespace dexel {

	class Lexer {
	
		string m_code;
		int m_position;
		char m_currentChar;
		vector<Token> m_tokens;

	public:
		Lexer(const string& code);

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

	};
}

#endif
