#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <list>
#include "Token.h"

using namespace std;

namespace dexel {

	class Lexer {
	
		string m_code;
		int m_position;
		char m_currentChar;

	public:
		Lexer(const string& code);

		void advance();
		list<Token> tokenize();

	};
}

#endif
