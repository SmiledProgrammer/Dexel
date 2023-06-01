#include "SyntaxComponent.h"

#include <iostream>
#include <fstream>
#include "FunctionCallComponent.h"
#include "FunctionDefinitionComponent.h"
#include "CommandComponent.h"
#include "ConditionComponent.h"
#include "VariableAssignmentComponent.h"

using namespace dexel;

// TODO: check if needed
// string SyntaxComponent::m_destinationPath = "";

SyntaxComponent::SyntaxComponent(vector<Token>& tokens, int index)
	: m_tokens(tokens), m_index(index) {}

void SyntaxComponent::readComponent() {
	throw "Unexpected internal error.";
}

string SyntaxComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	throw "Unexpected internal error.";
}

void SyntaxComponent::setGlobalDestinationDirectoryPath(const string& dirPath) {
	m_destinationDirectoryPath = dirPath;
}

Token SyntaxComponent::getNextToken() {
	return m_tokens[m_index++];
}

vector<SyntaxComponent> SyntaxComponent::readComponentsBlock() {
	vector<SyntaxComponent> components;
	Token openBrace = getNextToken();
	if (openBrace.getType() != Token::TYPE_LEFT_BRACES_SEPARATOR) {
		throw "Expected beginning of braces block here.";
		// TODO: make throws everywhere instead of printError()
	}
	try {
		while (m_tokens.at(m_index).getType() != Token::TYPE_RIGHT_BRACES_SEPARATOR) {
			SyntaxComponent component = createComponentFromNextToken();
			components.push_back(component);
		}
		getNextToken();
	} catch (out_of_range ex) {
		throw "Expected end of braces block here.";
	}
	return components;
}

void SyntaxComponent::checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes) {
	for (int i = 0; i < nextTokensTypes.size(); i++) {
		Token nextTokenType = getNextToken().getType();
		Token::Type expectedType = nextTokensTypes[i];
		if (nextTokenType != expectedType) {
			throw "Expected token here of type: " + Token::typeToString(expectedType);
		}
	}
}

void SyntaxComponent::createMCFunctionFile(const string& functionName, const string& dexelCode) {
	string filepath = m_destinationDirectoryPath + "/" + functionName + ".mcfunction";
	ofstream fileStream(filepath);
	fileStream << dexelCode << endl;
	fileStream.close();
}

SyntaxComponent SyntaxComponent::createComponentFromNextToken() {
	switch (getNextToken().getType()) {
	case Token::TYPE_COMMAND: return CommandComponent(m_tokens, m_index - 1);
	case Token::TYPE_IF_KEYWORD: return ConditionComponent(m_tokens, m_index - 1);
	case Token::TYPE_IDENTIFIER:
		Token::Type tokenType = getNextToken().getType();
		if (tokenType == Token::TYPE_EQUALS_OPERATOR) {
			return VariableAssignmentComponent(m_tokens, m_index - 2);
		} else if (tokenType == Token::TYPE_LEFT_PARENTHESES_SEPARATOR) {
			return FunctionCallComponent(m_tokens, m_index - 2);
		}
	}
	throw "Cannot parse code structure.";
}