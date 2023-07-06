#include "FunctionDefinitionComponent.h"

using namespace dexel;

const vector<Token::Type> FunctionDefinitionComponent::m_startingPattern{
	Token::TYPE_FUNCTION_KEYWORD,
	Token::TYPE_IDENTIFIER,
	Token::TYPE_LEFT_PARENTHESES_SEPARATOR,
	Token::TYPE_RIGHT_PARENTHESES_SEPARATOR
};

FunctionDefinitionComponent::FunctionDefinitionComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

void FunctionDefinitionComponent::readComponent() {
	int identifierIndex = m_index + 1;
	checkNextTokensTypes(m_startingPattern);
	m_functionName = m_tokens[identifierIndex].getValue();
	m_insideFunctionComponents = readComponentsBlock();
}

string FunctionDefinitionComponent::convertToMCFunctionCode(const string& destinationFilepath) {

}
