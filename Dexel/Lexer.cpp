#include "Lexer.h"

#include <cctype>
#include "LanguageConstants.h"
#include "StringUtils.h"

using namespace dexel;

const char COMMENT_CHAR = '#';
const char EXPRESSION_SEPARATOR_CHAR = ';';
const char CONDITION_TERMINATING_CHAR = ')';

Lexer::Lexer(const string& code, const string& sourceCodeFilepath) {
	m_code = code;
	m_sourceCodeFilepath = sourceCodeFilepath;
	m_position = -1;
	m_line = 1;
	m_column = 0;
	m_currentChar = NULL;
	advance();
}

vector<Token> Lexer::tokenize() {
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
					return vector<Token>({ createToken(Token::TYPE_UNKNOWN_SYMBOL) });
				}
			}
		}
	}
	return m_tokens;
}

void Lexer::advance() {
	m_position++;
	m_currentChar = m_position < m_code.length() ? m_code[m_position] : NULL;
	if (m_currentChar == '\n') {
		m_line++;
		m_column = 1;
	} else {
		m_column++;
	}
}

void Lexer::processComment() {
	do {
		advance();
	} while (m_currentChar != '\n' && m_currentChar != NULL);
}

void Lexer::processSymbol(Token::Type symbolTokenType) {
	m_tokens.push_back(createToken(symbolTokenType));
	advance();
}

void Lexer::processInteger() {
	string integerStr;
	do {
		integerStr += m_currentChar;
		advance();
	} while (isdigit(m_currentChar));
	m_tokens.push_back(createToken(Token::TYPE_INTEGER_LITERAL, integerStr));
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
		} else if (m_tokens.size() > 0 && m_tokens.back().getType() == Token::TYPE_LEFT_PARENTHESES_SEPARATOR && CONDITION_KEYWORDS.contains(expression)) {
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
	expression = removeNewlines(expression);
	m_tokens.push_back(createToken(Token::TYPE_COMMAND, expression));
}

void Lexer::processCondition(string& expression) {
	do {
		expression += m_currentChar;
		advance();
	} while (m_currentChar != CONDITION_TERMINATING_CHAR && m_currentChar != NULL);
	expression = removeNewlines(expression);
	m_tokens.push_back(createToken(Token::TYPE_CONDITION, expression));
}

void Lexer::processDexelKeyword(Token::Type keywordTokenType, const string& keyword) {
	m_tokens.push_back(createToken(keywordTokenType));
}

void Lexer::processIdentifier(const string& identifier) {
	m_tokens.push_back(createToken(Token::TYPE_IDENTIFIER, identifier));
}

bool Lexer::isIdentifierCharacter(char c) {
	return isalnum(c) || c == '_' || c == '@';
}

Token Lexer::createToken(Token::Type type, const string& value) {
	return Token(type, m_sourceCodeFilepath, m_line, m_column, value);
}
