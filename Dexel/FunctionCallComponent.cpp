#include "FunctionCallComponent.h"

#include "LanguageConstants.h"

using namespace dexel;

const vector<Token::Type> FunctionCallComponent::m_functionCallPattern{
	Token::TYPE_IDENTIFIER,
	Token::TYPE_LEFT_PARENTHESES_SEPARATOR,
	Token::TYPE_RIGHT_PARENTHESES_SEPARATOR,
	Token::TYPE_SEMICOLON_SEPARATOR
};


FunctionCallComponent::FunctionCallComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {
	readComponent();
}

void FunctionCallComponent::readComponent() {
	int functionNameIndex = m_index;
	checkNextTokensTypes(m_functionCallPattern);
	m_functionName = m_tokens[functionNameIndex].getValue();
}

string FunctionCallComponent::convertToMCFunctionCode(const string& functionNamePrefix) {
	return "function " + DEXEL_DATAPACK_NAMESPACE + ":" + m_functionName + "\n";
}
