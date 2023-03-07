#include "Token.h"

using namespace dexel;

Token::Token(Type type, const string& value)
	: m_type(type), m_value(value) {}
