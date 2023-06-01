#include "VariableAssignmentComponent.h"

using namespace dexel;

const vector<Token::Type> VariableAssignmentComponent::m_startingPattern{
	Token::TYPE_IDENTIFIER,
	Token::TYPE_EQUALS_OPERATOR
};

const map<Token::Type, int> VariableAssignmentComponent::m_operatorsPrecedence{
	{Token::TYPE_PLUS_OPERATOR, 1},
	{Token::TYPE_HYPHEN_OPERATOR, 1},
	{Token::TYPE_ASTERISK_OPERATOR, 2},
	{Token::TYPE_FORWARD_SLASH_OPERATOR, 2}
};


VariableAssignmentComponent::VariableAssignmentComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

void VariableAssignmentComponent::readComponent() { // TODO: add reading semicolon at the end
	int variableNameIndex = m_index;
	checkNextTokensTypes(m_startingPattern);
	m_variableName = m_tokens[variableNameIndex].getValue();
	if (!isAssignmentExpressionValid()) {
		throw "Assignment expression is not valid.";
	}
	m_numericValue = parseNumericValue(m_index);
	// TODO
}

string VariableAssignmentComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	
}

bool VariableAssignmentComponent::isAssignmentExpressionValid() {
	int index = m_index;
	while (m_tokens[index] != Token::TYPE_SEMICOLON_SEPARATOR) {

		index++;
		if (index == m_tokens.size()) {
			throw "Expected semicolon but got end of file.";
		}
	}
}

NumericValue VariableAssignmentComponent::parseNumericValue(int startingTokenIndex) {

}
