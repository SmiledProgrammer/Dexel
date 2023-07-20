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
			m_components.push_back(functionComponent);
			m_index = functionComponent.getCurrentIndex();
		} else {
			throw createException("Dexel file can only contain function definitions.");
		}
	}
}

string DexelFileSyntaxComponent::convertToMCFunctionCode(const string& functionNamePrefix) {
	for (FunctionDefinitionComponent component : m_components) {
		component.convertToMCFunctionCode("");
	}
	return "";
}
