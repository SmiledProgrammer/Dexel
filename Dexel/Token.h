#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

namespace dexel {

	class Token {
	public:
		enum Type {
			TYPE_COMMAND,
			TYPE_IDENTIFIER,
			TYPE_FUNCTION_KEYWORD,
			TYPE_IF_KEYWORD,
			TYPE_INT_KEYWORD,
			TYPE_INTEGER_LITERAL,
			TYPE_EQUALS_OPERATOR,
			TYPE_PLUS_OPERATOR,
			TYPE_HYPHEN_OPERATOR,
			TYPE_ASTERISK_OPERATOR,
			TYPE_FORWARD_SLASH_OPERATOR,
			TYPE_SEMICOLON_SEPARATOR,
			TYPE_LEFT_PARENTHESES_SEPARATOR,
			TYPE_RIGHT_PARENTHESES_SEPARATOR,
			TYPE_LEFT_BRACES_SEPARATOR,
			TYPE_RIGHT_BRACES_SEPARATOR,
			TYPE_HASH_COMMENT
		};

	private:
		Type m_type;
		string m_value;

	public:
		Token(Type type, const string& value = "");

		inline Type getType() { return m_type; }
		inline string getValue() { return m_value; }

	};
}

#endif
