#include "Parser.h"

#include <iostream>

using namespace dexel;

Parser::Parser(vector<Token>& tokens, const string& filepath) {
	DexelFileSyntaxComponent dexelFile(tokens, filepath);
	m_dexelFileComponents.push_back(dexelFile);
}

vector<DexelFileSyntaxComponent> Parser::parse() {
	for (DexelFileSyntaxComponent dexelFile : m_dexelFileComponents) {
		try {
			bool parsed = dexelFile.readComponent();
		} catch (string ex) {
			cerr << "[ERROR] Failed to parse file \"" << dexelFile.getFilepath() << "\": " << ex << endl;
			return vector<DexelFileSyntaxComponent>();
		}
	}
	return m_dexelFileComponents;
}
