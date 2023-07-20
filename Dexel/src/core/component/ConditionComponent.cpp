#include "ConditionComponent.h"

#include <sstream>
#include "../LanguageConstants.h"

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

int ConditionComponent::m_mcFunctionConditionCounter = 0;


ConditionComponent::ConditionComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {
	readComponent();
}

void ConditionComponent::readComponent() {
	int ifConditionIndex = m_index + 2;
	checkNextTokensTypes(m_ifBlockStartingPattern);
	string ifCondition = m_tokens[ifConditionIndex].getValue();
	vector<shared_ptr<SyntaxComponent>> ifBlockComponents = readComponentsBlock();
	m_conditionBlocks.push_back(ConditionBlock(ifCondition, ifBlockComponents));
	while (m_index + 1 < m_tokens.size() && m_tokens[m_index].getType() == Token::TYPE_ELSE_KEYWORD) {
		if (m_tokens[m_index + 1].getType() == Token::TYPE_IF_KEYWORD) {
			int elseIfConditionIndex = m_index + 3;
			checkNextTokensTypes(m_elseIfBlockStartingPattern);
			string elseIfCondition = m_tokens[elseIfConditionIndex].getValue();
			vector<shared_ptr<SyntaxComponent>> elseIfBlockComponents = readComponentsBlock();
			m_conditionBlocks.push_back(ConditionBlock(elseIfCondition, elseIfBlockComponents));
		} else {
			getNextToken();
			vector<shared_ptr<SyntaxComponent>> elseBlockComponents = readComponentsBlock();
			m_conditionBlocks.push_back(ConditionBlock(ELSE_CONDITION_STRING, elseBlockComponents));
		}
	}
}

string ConditionComponent::convertToMCFunctionCode(const string& functionNamePrefix) {
	stringstream code;
	code << "scoreboard players add .condition_met_counter dexel_helpers 1" << endl;
	code << "scoreboard players operation .condition_marker dexel_helpers = .condition_met_counter dexel_helpers" << endl;

	string executeCommand = "execute if score .condition_marker dexel_helpers = .condition_met_counter dexel_helpers";
	for (int i = 0; i < m_conditionBlocks.size(); i++) {
		string generatedFunctionName = getNextConditionFunctionName(functionNamePrefix);
		ConditionBlock conditionBlock = m_conditionBlocks[i];
		string conditionCode = convertComponentsBlockToMCFunctionCode(generatedFunctionName, conditionBlock.insideComponents);
		conditionCode += "scoreboard players add .condition_met_counter dexel_helpers 1\n";
		createMCFunctionFile(generatedFunctionName, conditionCode);

		if (i == 0) {
			code << "execute if " << conditionBlock.condition << " run function " << DEXEL_DATAPACK_NAMESPACE << ":" << generatedFunctionName << endl;
		} else {
			executeCommand += " unless " + m_conditionBlocks[i - 1].condition;
			if (conditionBlock.condition == "ELSE") {
				code << executeCommand << " run function " << DEXEL_DATAPACK_NAMESPACE << ":" << generatedFunctionName << endl;
			} else {
				code << executeCommand << " if " + conditionBlock.condition << " run function " << DEXEL_DATAPACK_NAMESPACE << ":" << generatedFunctionName << endl;
			}
		}
	}
	return code.str();
}

string ConditionComponent::getNextConditionFunctionName(const string& functionNamePrefix) {
	return functionNamePrefix + "-cond-" + to_string(m_mcFunctionConditionCounter++);
}
