#include "ConditionComponent.h"

const string ELSE_CONDITION_STRING = "ELSE";

using namespace dexel;

ConditionComponent::ConditionComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

bool ConditionComponent::readComponent() {
	Token ifToken = getNextToken();
	if (ifToken.getType() != Token::TYPE_IF_KEYWORD) {
		throw "Unexpected internal error.";
	}
	// TODO: loop this
	string condition = readCondition();
	if (condition == "") {
		throw "Failed to read condition.";
	}
	vector<SyntaxComponent> components = readComponentsBlock();
	ConditionBlock conditionBlock(condition, components);
	m_conditionBlocks.push_back(conditionBlock);
}

string ConditionComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	for (ConditionBlock block : m_conditionBlocks) {
		// TODO
	}
	// TODO
}

string ConditionComponent::readCondition() {

}
