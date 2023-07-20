#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "component/DexelFileSyntaxComponent.h"

namespace dexel {

	/**
	 * \brief Klasa do parsowania.
	 *
	 * Klasa służąca do parsowania tokenów języka Dexel.
	 */
	class Parser {

		vector<DexelFileSyntaxComponent> m_dexelFileComponents;

	public:
		Parser(vector<Token>& tokens, const string& filepath);

		/**
		 * \brief Funkcja do parsowania.
		 *
		 * Funkcja parsująca tokeny języka Dexel.
		 *
		 * \return Lista komponentów plików języka Dexel.
		 */
		vector<DexelFileSyntaxComponent> parse();
	};
}

#endif
