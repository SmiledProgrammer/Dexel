#include "Parser.h"

#include <iostream>
#include "ParsingException.h"

using namespace dexel;

Parser::Parser(vector<Token>& tokens, const string& filepath) {
	DexelFileSyntaxComponent dexelFile(tokens, filepath);
	m_dexelFileComponents.push_back(dexelFile);
}

vector<DexelFileSyntaxComponent> Parser::parse() {
	for (DexelFileSyntaxComponent& dexelFile : m_dexelFileComponents) {
		try {
			dexelFile.readComponent();
		} catch (ParsingException ex) {
			cerr << "[ERROR] File parsing error: " << ex.getMessage() << endl;
			cerr << "        at file \"" << ex.getFilepath() << "\", line: " << ex.getLine() << ", column: " << ex.getColumn() << endl;
			return vector<DexelFileSyntaxComponent>();
		}
	}
	return m_dexelFileComponents;
}
