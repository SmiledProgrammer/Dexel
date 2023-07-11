#include "ConditionComponent.h"

using namespace dexel;

const string ELSE_CONDITION_STRING = "ELSE";

const vector<Token::Type> ConditionComponent::m_ifBlockStartingPattern{
	Token::TYPE_IF_KEYWORD,
	Token::TYPE_LEFT_PARENTHESES_SEPARATOR,
	Token::TYPE_CONDITION,
	Token::TYPE_RIGHT_PARENTHESES_SEPARATOR
};

const vector<Token::Type> ConditionComponent::m_elseIfBlockStartingPattern{
	Token::TYPE_ELSE_KEYWORD,
	Token::TYPE_IF_KEYWORD,
	Token::TYPE_LEFT_PARENTHESES_SEPARATOR,
	Token::TYPE_CONDITION,
	Token::TYPE_RIGHT_PARENTHESES_SEPARATOR
};


ConditionComponent::ConditionComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {}

void ConditionComponent::readComponent() {
	int ifConditionIndex = m_index + 2;
	checkNextTokensTypes(m_ifBlockStartingPattern);
	string ifCondition = m_tokens[ifConditionIndex].getValue();
	vector<SyntaxComponent> ifBlockComponents = readComponentsBlock();
	m_conditionBlocks.push_back(ConditionBlock(ifCondition, ifBlockComponents));
	while (m_index + 1 < m_tokens.size() && m_tokens[m_index].getType() == Token::TYPE_ELSE_KEYWORD) {
		if (m_tokens[m_index + 1].getType() == Token::TYPE_IF_KEYWORD) {
			int elseIfConditionIndex = m_index + 3;
			checkNextTokensTypes(m_elseIfBlockStartingPattern);
			string elseIfCondition = m_tokens[elseIfConditionIndex].getValue();
			vector<SyntaxComponent> elseIfBlockComponents = readComponentsBlock();
			m_conditionBlocks.push_back(ConditionBlock(elseIfCondition, elseIfBlockComponents));
		} else {
			vector<SyntaxComponent> elseBlockComponents = readComponentsBlock();
			m_conditionBlocks.push_back(ConditionBlock(ELSE_CONDITION_STRING, elseBlockComponents));
		}
	}
}

string ConditionComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	for (ConditionBlock block : m_conditionBlocks) {
		// TODO
	}
	// TODO
	return "";
}
