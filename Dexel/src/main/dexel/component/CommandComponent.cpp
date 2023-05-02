#include "CommandComponent.h"

using namespace dexel;

CommandComponent::CommandComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

void CommandComponent::readComponent() {
	Token commandToken = getNextToken();
	if (commandToken.getType() != Token::TYPE_COMMAND) {
		throw "Expected a minecraft command here";
	}
	m_commandExpression = commandToken.getValue();
}

string CommandComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	return m_commandExpression + "\n";
}
