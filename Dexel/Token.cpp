#include "Token.h"

using namespace dexel;

Token::Token(Type type, const string& value)
	: m_type(type), m_value(value) {}

string Token::typeToString(Type type) {
	switch (type) {
	case TYPE_COMMAND: return "Minecraft command";
	case TYPE_CONDITION: return "Condition";
	case TYPE_IDENTIFIER: return "Identifier";
	case TYPE_FUNCTION_KEYWORD: return "\"function\" keyword";
	case TYPE_IF_KEYWORD: return "\"if\" keyword";
	case TYPE_ELSE_KEYWORD: return "\"else\" keyword";
	case TYPE_INT_KEYWORD: return "\"int\" keyword";
	case TYPE_INTEGER_LITERAL: return "Integer literal";
	case TYPE_EQUALS_OPERATOR: return "Equals sign";
	case TYPE_PLUS_OPERATOR: return "Plus sign";
	case TYPE_HYPHEN_OPERATOR: return "Hyphen";
	case TYPE_ASTERISK_OPERATOR: return "Asterisk";
	case TYPE_FORWARD_SLASH_OPERATOR: "Forward slash";
	case TYPE_SEMICOLON_SEPARATOR: return "Semicolon";
	case TYPE_LEFT_PARENTHESES_SEPARATOR: return "Left parenthese";
	case TYPE_RIGHT_PARENTHESES_SEPARATOR: return "Right parenthese";
	case TYPE_LEFT_BRACES_SEPARATOR: return "Left brace";
	case TYPE_RIGHT_BRACES_SEPARATOR: return "Right brace";
	case TYPE_HASH_COMMENT: return "Hash";
	default: return "Unknown symbol";
	}
}
