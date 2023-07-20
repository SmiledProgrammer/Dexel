#include "SyntaxComponent.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include "FunctionCallComponent.h"
#include "FunctionDefinitionComponent.h"
#include "CommandComponent.h"
#include "ConditionComponent.h"
#include "VariableAssignmentComponent.h"
#include "LanguageConstants.h"

using namespace dexel;

// TODO: Bug - gdy definiujac funkcje nie da sie zamykajacego nawiasu klamerkowego, to jakis out of range leci czy cos
//       > moze rozwiazaniem byloby dodanie sprawdzania czy indeks nie wychodzi poza zakres w funkcji getNextToken() ?

string SyntaxComponent::m_outputFunctionsDirectoryPath = "";
bool SyntaxComponent::m_overrideFiles = true;

SyntaxComponent::SyntaxComponent(vector<Token>& tokens, int index)
	: m_tokens(tokens), m_index(index) {}

void SyntaxComponent::readComponent() {
	throw createException("Unexpected internal error.");
}

string SyntaxComponent::convertToMCFunctionCode(const string& functionNamePrefix) {
	throw createException("Unexpected internal error.");
}

void SyntaxComponent::setGlobalSettings(const string& destinationDirectoryPath, bool overrideFiles) {
	m_outputFunctionsDirectoryPath = destinationDirectoryPath + "\\" + DEXEL_DATAPACK_NAME + "\\data\\" + DEXEL_DATAPACK_NAMESPACE + "\\functions";
	m_overrideFiles = overrideFiles;
}

Token SyntaxComponent::getNextToken() {
	return m_tokens[m_index++];
}

vector<shared_ptr<SyntaxComponent>> SyntaxComponent::readComponentsBlock() {
	vector<shared_ptr<SyntaxComponent>> components;
	Token openBrace = getNextToken();
	if (openBrace.getType() != Token::TYPE_LEFT_BRACES_SEPARATOR) {
		throw createException("Expected beginning of braces block here.");
	}
	try {
		while (m_tokens.at(m_index).getType() != Token::TYPE_RIGHT_BRACES_SEPARATOR) {
			shared_ptr<SyntaxComponent> component = createComponentFromNextToken();
			components.push_back(component);
			m_index = component->getCurrentIndex();
		}
		getNextToken();
	} catch (out_of_range ex) {
		throw createException("Expected end of braces block here.");
	}
	return components;
}

string SyntaxComponent::convertComponentsBlockToMCFunctionCode(const string& functionName, const vector<shared_ptr<SyntaxComponent>>& componentsBlock) {
	string code = "";
	for (shared_ptr<SyntaxComponent> component : componentsBlock) {
		code += component->convertToMCFunctionCode(functionName);
	}
	return code;
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
	string filepath = m_outputFunctionsDirectoryPath + "\\" + functionName + ".mcfunction";
	if (m_overrideFiles || !filesystem::exists(filepath)) {
		ofstream fileStream(filepath);
		fileStream << dexelCode << endl;
		fileStream.close();
	} else {
		cout << "[WARN] File \"" + filepath + "\" already exists and will not be overridden." << endl;
	}
}

shared_ptr<SyntaxComponent> SyntaxComponent::createComponentFromNextToken() {
	Token::Type nextTokenType = getNextToken().getType();
	switch (nextTokenType) {
	case Token::TYPE_COMMAND: return make_shared<CommandComponent>(m_tokens, m_index - 1);
	case Token::TYPE_IF_KEYWORD: return make_shared<ConditionComponent>(m_tokens, m_index - 1);
	case Token::TYPE_IDENTIFIER: return make_shared<FunctionCallComponent>(m_tokens, m_index - 1);
	case Token::TYPE_INT_KEYWORD: return make_shared<VariableAssignmentComponent>(m_tokens, m_index - 1);
	}
	throw createException("Cannot parse code structure.");
}

ParsingException<string> SyntaxComponent::createException(const string& message) {
	Token currentToken = m_tokens[m_index];
	return ParsingException(message, currentToken.getFilepath(), currentToken.getLine(), currentToken.getColumn());
}
