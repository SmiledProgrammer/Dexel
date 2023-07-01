#include "VariableAssignmentComponent.h"

using namespace dexel;

const vector<Token::Type> VariableAssignmentComponent::m_startingPattern{
	Token::TYPE_IDENTIFIER,
	Token::TYPE_EQUALS_OPERATOR
};

const map<NumericOperator, int> VariableAssignmentComponent::m_operatorsPrecedence{
	{ NumericOperator::ADD, 1 },
	{ NumericOperator::SUBTRACT, 1 },
	{ NumericOperator::MULTIPLY, 2 },
	{ NumericOperator::DIVIDE, 2 }
};


VariableAssignmentComponent::VariableAssignmentComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index), m_lastOperationRead(Token::TYPE_UNKNOWN_SYMBOL) {}

void VariableAssignmentComponent::readComponent() {
	int variableNameIndex = m_index;
	checkNextTokensTypes(m_startingPattern);
	m_variableName = m_tokens[variableNameIndex].getValue();
	if (!isAssignmentExpressionValid()) {
		throw "Assignment expression is not valid.";
	}
	m_numericValue = parseNumericValue(m_index);
	m_index++;
}

string VariableAssignmentComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	// TODO
}

bool VariableAssignmentComponent::isAssignmentExpressionValid() {
	int index = m_index;
	bool containsOperand = false;
	bool expectedOperator = false;
	int parenthesesDepth = 0;
	while (m_tokens[index].getType() != Token::TYPE_SEMICOLON_SEPARATOR) {
		switch (m_tokens[index].getType()) {
		case Token::TYPE_PLUS_OPERATOR:
		case Token::TYPE_HYPHEN_OPERATOR:
		case Token::TYPE_ASTERISK_OPERATOR:
		case Token::TYPE_FORWARD_SLASH_OPERATOR:
			if (!expectedOperator) throw "Expected operand here.";
			expectedOperator = false;
			break;
		case Token::TYPE_IDENTIFIER:
		case Token::TYPE_INTEGER_LITERAL:
			if (expectedOperator) throw "Expected operator here.";
			expectedOperator = true;
			containsOperand = true;
			break;
		case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
			if (expectedOperator) throw "Expected operator here but found opening parentheses.";
			parenthesesDepth++;
			break;
		case Token::TYPE_RIGHT_PARENTHESES_SEPARATOR:
			if (!expectedOperator) throw "Expected operand here but found closing parentheses.";
			if (parenthesesDepth == 0) throw "Unexpected redundant closing parentheses.";
			parenthesesDepth--;
			break;
		default:
			throw "Unexpected token type.";
		}
		index++;
		if (index == m_tokens.size()) throw "Expected semicolon but got end of file.";
	}
	if (!containsOperand) throw "Expression is expected to contain at least one operand.";
	if (!expectedOperator) throw "Expression must end with an operand rather than operator.";
}

NumericValue VariableAssignmentComponent::parseNumericValue(int& index) {
	NumericValue numericValue;
	NumericOperator lastOperator;
	while (m_tokens[index] != Token::TYPE_RIGHT_PARENTHESES_SEPARATOR &&
		m_tokens[index] != Token::TYPE_SEMICOLON_SEPARATOR)
	{
		switch (m_tokens[index].getType()) {
		case Token::TYPE_PLUS_OPERATOR:
		case Token::TYPE_HYPHEN_OPERATOR:
		case Token::TYPE_ASTERISK_OPERATOR:
		case Token::TYPE_FORWARD_SLASH_OPERATOR:
			NumericOperator thisOperator = readNumericValueOperator(index);
			if (numericValue.getNumericValueType() == NumericValue::OPERATION_VALUE &&
				hasOperatorHigherPrecedence(thisOperator, lastOperator))
			{
				OperationValue lastOperation = dynamic_cast<OperationValue&>(numericValue);
				NumericValue lowerPrecedenceOperand = lastOperation.leftOperand;
				NumericValue newOperationLeftOperand = lastOperation.rightOperand;
				NumericValue newOperationRightOperand = readOperandNumericValue(++index);
				OperationValue newOperation = OperationValue(newOperationLeftOperand, newOperationRightOperand, thisOperator);
				numericValue = OperationValue(lowerPrecedenceOperand, newOperation, lastOperator);
			} else {
				lastOperator = thisOperator;
			}
			break;
		
		case Token::TYPE_IDENTIFIER:
		case Token::TYPE_INTEGER_LITERAL:
		case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
			NumericValue operand = readOperandNumericValue(index);
			if (numericValue.getNumericValueType() == NumericValue::NONE) {
				numericValue = operand;
			} else {
				OperationValue operationValue = OperationValue(numericValue, operand, lastOperator);
			}
			break;
		}
		index++;
	}
	index++;
	return tryToSimplifyNumericValue(numericValue);
}

NumericValue VariableAssignmentComponent::readOperandNumericValue(int& index) {
	switch (m_tokens[index].getType()) {
	case Token::TYPE_IDENTIFIER:
		return IdentifierValue(m_tokens[index].getValue());
	case Token::TYPE_INTEGER_LITERAL:
		return LiteralIntegerValue(stoi(m_tokens[index].getValue()));
	case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
		return parseNumericValue(++index);
	}
	throw "Internal error. Expected identifier, literal or opening parentheses here.";
}

NumericOperator VariableAssignmentComponent::readNumericValueOperator(int index) {
	switch (m_tokens[index].getType()) {
	case Token::TYPE_PLUS_OPERATOR: return NumericOperator::ADD;
	case Token::TYPE_HYPHEN_OPERATOR: return NumericOperator::SUBTRACT;
	case Token::TYPE_ASTERISK_OPERATOR: return NumericOperator::MULTIPLY;
	case Token::TYPE_FORWARD_SLASH_OPERATOR: return NumericOperator::DIVIDE;
	}
	throw "Internal error. Expected operator here.";
}

bool VariableAssignmentComponent::hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator) {
	int thisPrecedence = m_operatorsPrecedence.find(thisOperator)->second;
	int otherPrecedence = m_operatorsPrecedence.find(otherOperator)->second;
	return thisPrecedence > otherPrecedence;
}

NumericValue VariableAssignmentComponent::tryToSimplifyNumericValue(NumericValue numericValue) {
	if (numericValue.getNumericValueType() == NumericValue::OPERATION_VALUE) {
		OperationValue operationValue = dynamic_cast<OperationValue&>(numericValue);
		return tryToSimplifyOperationValue(operationValue);
	}
	return numericValue;
}

NumericValue VariableAssignmentComponent::tryToSimplifyOperationValue(OperationValue operationValue) {
	operationValue.leftOperand = tryToSimplifyNumericValue(operationValue.leftOperand);
	operationValue.rightOperand = tryToSimplifyNumericValue(operationValue.rightOperand);
	if (operationValue.leftOperand.getNumericValueType() == NumericValue::LITERAL_INTEGER_VALUE &&
		operationValue.rightOperand.getNumericValueType() == NumericValue::LITERAL_INTEGER_VALUE)
	{
		int leftValue = dynamic_cast<LiteralIntegerValue&>(operationValue.leftOperand).intValue;
		int rightValue = dynamic_cast<LiteralIntegerValue&>(operationValue.rightOperand).intValue;
		switch (operationValue.numericOperator) {
		case NumericOperator::ADD: return LiteralIntegerValue(leftValue + rightValue);
		case NumericOperator::SUBTRACT: return LiteralIntegerValue(leftValue - rightValue);
		case NumericOperator::MULTIPLY: return LiteralIntegerValue(leftValue * rightValue);
		case NumericOperator::DIVIDE: return LiteralIntegerValue(leftValue / rightValue);
		}
	}
	return operationValue;
}
