#include "SyntaxComponent.h"

#include <iostream>
#include <fstream>
#include "FunctionCallComponent.h"
#include "FunctionDefinitionComponent.h"
#include "CommandComponent.h"
#include "ConditionComponent.h"
#include "VariableAssignmentComponent.h"

using namespace dexel;

// TODO: Bug - gdy definiujac funkcje nie da sie zamykajacego nawiasu klamerkowego, to jakis out of range leci czy cos

// TODO: check if needed
string SyntaxComponent::m_destinationDirectoryPath = "";

SyntaxComponent::SyntaxComponent(vector<Token>& tokens, int index)
	: m_tokens(tokens), m_index(index) {}

void SyntaxComponent::readComponent() {
	throw createException("Unexpected internal error.");
}

string SyntaxComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	throw createException("Unexpected internal error.");
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
		throw createException("Expected beginning of braces block here.");
	}
	try {
		while (m_tokens.at(m_index).getType() != Token::TYPE_RIGHT_BRACES_SEPARATOR) {
			Token::Type tokenType = m_tokens.at(m_index).getType(); // TODO: usun
			SyntaxComponent component = createComponentFromNextToken();
			components.push_back(component);
			m_index = component.getCurrentIndex();
		}
		getNextToken();
	} catch (out_of_range ex) {
		throw createException("Expected end of braces block here.");
	}
	return components;
}

void SyntaxComponent::checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes) {
	for (int i = 0; i < nextTokensTypes.size(); i++) {
		Token::Type nextTokenType = getNextToken().getType();
		Token::Type expectedType = nextTokensTypes[i];
		if (nextTokenType != expectedType) {
			throw createException("Expected token here of type: " + Token::typeToString(expectedType));
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
	Token::Type nextTokenType = getNextToken().getType();
	switch (nextTokenType) {
	case Token::TYPE_COMMAND: return CommandComponent(m_tokens, m_index - 1);
	case Token::TYPE_IF_KEYWORD: return ConditionComponent(m_tokens, m_index - 1);
	case Token::TYPE_IDENTIFIER: return FunctionCallComponent(m_tokens, m_index - 1);
	case Token::TYPE_INT_KEYWORD: return VariableAssignmentComponent(m_tokens, m_index - 1);
	}
	throw createException("Cannot parse code structure.");
}

ParsingException SyntaxComponent::createException(const string& message) {
	Token currentToken = m_tokens[m_index];
	return ParsingException(message, currentToken.getFilepath(), currentToken.getLine(), currentToken.getColumn());
}
