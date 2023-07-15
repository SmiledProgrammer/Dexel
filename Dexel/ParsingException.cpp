#include "ParsingException.h"

using namespace dexel;

ParsingException::ParsingException(const string& message, const string& filepath, int line, int column)
	: m_message(message), m_filepath(filepath), m_line(line), m_column(column) {}
