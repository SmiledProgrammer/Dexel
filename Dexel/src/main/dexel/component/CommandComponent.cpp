#include "CommandComponent.h"

using namespace dexel;

const vector<Token::Type> CommandComponent::m_commandExpressionPattern{
	Token::TYPE_COMMAND,
	Token::TYPE_SEMICOLON_SEPARATOR
};


CommandComponent::CommandComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

void CommandComponent::readComponent() {
	int commandIndex = m_index;
	checkNextTokensTypes(m_commandExpressionPattern);
	Token commandToken = m_tokens[commandIndex];
	m_commandExpression = commandToken.getValue();
}

string CommandComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	return m_commandExpression + "\n";
}
