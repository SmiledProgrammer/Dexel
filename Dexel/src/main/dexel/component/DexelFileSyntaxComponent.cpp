#include "DexelFileSyntaxComponent.h"

#include "FunctionDefinitionComponent.h"

using namespace dexel;

DexelFileSyntaxComponent::DexelFileSyntaxComponent(vector<Token>& tokens, const string& filepath)
	: SyntaxComponent(tokens, 0), m_filepath(filepath) {}

void DexelFileSyntaxComponent::readComponent() {
	while (m_index < m_tokens.size()) {
		Token token = getNextToken();
		if (token.getType() == Token::TYPE_FUNCTION_KEYWORD) {
			FunctionDefinitionComponent functionComponent(m_tokens, m_index - 1);
			functionComponent.readComponent();
			m_components.push_back(functionComponent);
		}
	}
}

string DexelFileSyntaxComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	
}
