#include "Lexer.h"

#include <map>
#include <cctype>

using namespace dexel;

const map<char, Token::Type> typeSymbols{
	{';', Token::TYPE_SEMICOLON},
	{'=', Token::TYPE_EQUALS},
	{'+', Token::TYPE_PLUS},
	{'-', Token::TYPE_HYPHEN},
	{'*', Token::TYPE_ASTERISK},
	{'/', Token::TYPE_FORWARD_SLASH},
	{'(', Token::TYPE_LEFT_PARENTHESES},
	{')', Token::TYPE_RIGHT_PARENTHESES},
	{'{', Token::TYPE_LEFT_BRACES},
	{'}', Token::TYPE_RIGHT_BRACES},
};

Lexer::Lexer(const string& code) {
	m_code = code;
	m_position = -1;
	m_currentChar = NULL;
	advance();
}

void Lexer::advance() {
	m_position++;
	m_currentChar = m_position < m_code.length() ? m_code[m_position] : NULL;
}

list<Token> Lexer::tokenize() {
	list<Token> tokens;
	while (m_currentChar != NULL) {
		if (isspace(m_currentChar)) {
			advance();
		} else {
			auto pos = typeSymbols.find(m_currentChar);
			if (pos != typeSymbols.end()) {
				Token::Type type = pos->second;
				tokens.push_back(Token(type, ""));
			} else {
				// TODO: loading Commands and Integers
			}
		}
	}
	return tokens;
}
