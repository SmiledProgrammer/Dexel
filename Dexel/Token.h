#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

namespace dexel {

	class Token {
	public:
		enum Type {
			TYPE_COMMAND,
			TYPE_INTEGER,
			TYPE_SEMICOLON,
			TYPE_EQUALS,
			TYPE_PLUS,
			TYPE_HYPHEN,
			TYPE_ASTERISK,
			TYPE_FORWARD_SLASH,
			TYPE_LEFT_PARENTHESES,
			TYPE_RIGHT_PARENTHESES,
			TYPE_LEFT_BRACES,
			TYPE_RIGHT_BRACES
		};

	private:
		Type m_type;
		string m_value;

	public:
		Token(Type type, const string& value);

	};
}

#endif
