#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

namespace dexel {

	class Token {
	public:
		enum Type {
			TYPE_UNKNOWN_SYMBOL,
			TYPE_COMMAND,
			TYPE_CONDITION,
			TYPE_IDENTIFIER,
			TYPE_FUNCTION_KEYWORD,
			TYPE_IF_KEYWORD,
			TYPE_ELSE_KEYWORD,
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
		string m_filepath;
		int m_line, m_column;
		string m_value;

	public:
		Token(Type type, const string& filepath, int line, int column, const string& value = "");

		static string typeToString(Type type);

		inline Type getType() const { return m_type; }
		inline const string& getFilepath() const { return m_filepath; }
		inline int getLine() const { return m_line; }
		inline int getColumn() const { return m_column; }
		inline const string& getValue() const { return m_value; }

		// TODO: move to source file
		friend bool operator==(const Token& left, const Token& right) {
			return left.getType() == right.getType() &&
				left.getValue() == right.getValue();
		}

		friend bool operator!=(const Token& left, const Token& right) {
			return !(left == right);
		}

	};
}

#endif
