#ifndef PARSING_EXCEPTION_H
#define PARSING_EXCEPTION_H

#include <string>

using namespace std;

namespace dexel {

	/**
	 * \brief Klasa wyjątku parsowania.
	 *
	 * Klasa pomocnicza zawierająca potrzebne dane wyjątków występujących przy parsowaniu.
	 */
	template<typename T>
	class ParsingException {

		T m_message;
		string m_filepath;
		int m_line, m_column;

	public:
		ParsingException(const T& message, const string& filepath, int line, int column)
			: m_message(message), m_filepath(filepath), m_line(line), m_column(column) {}

		inline const T& getMessage() const { return m_message; }
		inline const string& getFilepath() const { return m_filepath; }
		inline int getLine() const { return m_line; }
		inline int getColumn() const { return m_column; }

	};
}

#endif
