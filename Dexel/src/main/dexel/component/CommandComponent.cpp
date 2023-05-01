#include "CommandComponent.h"

using namespace dexel;

CommandComponent::CommandComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

bool CommandComponent::readComponent() {
	Token commandToken = getNextToken();
	if (commandToken.getType() == Token::TYPE_COMMAND) {
		m_commandExpression = commandToken.getValue();
		return true;
	}
	return false;
}

string CommandComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	return m_commandExpression + "\n";
}
