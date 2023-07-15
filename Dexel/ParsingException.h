#ifndef PARSING_EXCEPTION_H
#define PARSING_EXCEPTION_H

#include <string>

using namespace std;

namespace dexel {

	class ParsingException {

		string m_message;
		string m_filepath;
		int m_line, m_column;

	public:
		ParsingException(const string& message, const string& filepath, int line, int column);

		inline const string& getMessage() const { return m_message; }
		inline const string& getFilepath() const { return m_filepath; }
		inline int getLine() const { return m_line; }
		inline int getColumn() const { return m_column; }

	};
}

#endif
