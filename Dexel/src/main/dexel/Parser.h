#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include "Token.h"
#include "component/DexelFileSyntaxComponent.h"

namespace dexel {

	class Parser {

		vector<DexelFileSyntaxComponent> m_dexelFileComponents;

	public:
		Parser(vector<Token>& tokens, const string& filepath);

		vector<DexelFileSyntaxComponent> parse();
	};
}

#endif
