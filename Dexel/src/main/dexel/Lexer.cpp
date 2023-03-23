#include "Lexer.h"

#include <cctype>
#include "LanguageConstants.h"
#include "StringUtils.h"

using namespace dexel;

const char COMMENT_CHAR = '#';
const char EXPRESSION_SEPARATOR_CHAR = ';';
const char CONDITION_TERMINATING_CHAR = ')';

Lexer::Lexer(const string& code) {
	m_code = code;
	m_position = -1;
	m_currentChar = NULL;
	advance();
}

list<Token> Lexer::tokenize() {
	while (m_currentChar != NULL) {
		if (isspace(m_currentChar)) {
			advance();
		} else if (m_currentChar == COMMENT_CHAR) {
			processComment();
		} else {
			auto symbolToken = SYMBOL_TOKENS.find(m_currentChar);
			if (symbolToken != SYMBOL_TOKENS.end()) {
				processSymbol(symbolToken->second);
			} else {
				if (isdigit(m_currentChar)) {
					processInteger();
				} else if (isalpha(m_currentChar)) {
					processExpression();
				} else {
					return list<Token>({ Token(Token::TYPE_UNKNOWN_SYMBOL) });
				}
			}
		}
	}
	return m_tokens;
}

void Lexer::advance() {
	m_position++;
	m_currentChar = m_position < m_code.length() ? m_code[m_position] : NULL;
}

void Lexer::processComment() {
	do {
		advance();
	} while (m_currentChar != '\n' && m_currentChar != NULL);
}

void Lexer::processSymbol(Token::Type symbolTokenType) {
	m_tokens.push_back(Token(symbolTokenType));
	advance();
}

void Lexer::processInteger() {
	string integerStr;
	do {
		integerStr += m_currentChar;
		advance();
	} while (isdigit(m_currentChar));
	m_tokens.push_back(Token(Token::TYPE_INTEGER_LITERAL, integerStr));
}

void Lexer::processExpression() {
	string expression;
	do {
		expression += m_currentChar;
		advance();
		// TODO: semicolon escaping
	} while (isIdentifierCharacter(m_currentChar));
	if (COMMAND_KEYWORDS.contains(expression)) {
		processCommand(expression);
	} else {
		auto keywordToken = DEXEL_KEYWORD_TOKENS.find(expression);
		if (keywordToken != DEXEL_KEYWORD_TOKENS.end()) {
			processDexelKeyword(keywordToken->second, expression);
		} else if (m_tokens.back().getType() == Token::TYPE_LEFT_PARENTHESES_SEPARATOR && CONDITION_KEYWORDS.contains(expression)) {
			processCondition(expression);
		} else {
			processIdentifier(expression);
		}
	}
}

void Lexer::processCommand(string& expression) {
	do {
		expression += m_currentChar;
		advance();
		// TODO: semicolon escaping
	} while (m_currentChar != EXPRESSION_SEPARATOR_CHAR && m_currentChar != NULL);
	expression = combineMultipleWhitespaces(expression);
	m_tokens.push_back(Token(Token::TYPE_COMMAND, expression));
}

void Lexer::processCondition(string& expression) {
	do {
		expression += m_currentChar;
		advance();
	} while (m_currentChar != CONDITION_TERMINATING_CHAR && m_currentChar != NULL);
	expression = combineMultipleWhitespaces(expression);
	m_tokens.push_back(Token(Token::TYPE_CONDITION, expression));
}

void Lexer::processDexelKeyword(Token::Type keywordTokenType, const string& keyword) {
	m_tokens.push_back(Token(keywordTokenType, keyword));
}

void Lexer::processIdentifier(const string& identifier) {
	m_tokens.push_back(Token(Token::TYPE_IDENTIFIER, identifier));
}

bool Lexer::isIdentifierCharacter(char c) {
	return isalnum(c) || c == '_' || c == '@';
}
