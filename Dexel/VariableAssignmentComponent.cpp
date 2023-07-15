#include "VariableAssignmentComponent.h"

using namespace dexel;

const vector<Token::Type> VariableAssignmentComponent::m_startingPattern{
	Token::TYPE_INT_KEYWORD,
	Token::TYPE_IDENTIFIER,
	Token::TYPE_EQUALS_OPERATOR
};

const map<NumericOperator, int> VariableAssignmentComponent::m_operatorsPrecedence{
	{ NumericOperator::NONE, -1 },
	{ NumericOperator::ADD, 1 },
	{ NumericOperator::SUBTRACT, 1 },
	{ NumericOperator::MULTIPLY, 2 },
	{ NumericOperator::DIVIDE, 2 }
};


VariableAssignmentComponent::VariableAssignmentComponent(vector<Token>& tokens, int index)
	: SyntaxComponent(tokens, index) {
	readComponent();
}

void VariableAssignmentComponent::readComponent() {
	int variableNameIndex = m_index;
	checkNextTokensTypes(m_startingPattern);
	m_variableName = m_tokens[variableNameIndex].getValue();
	if (!isAssignmentExpressionValid()) {
		throw createException("Assignment expression is not valid.");
	}
	m_numericValue = *parseNumericValue(m_index);
	m_index++;
}

string VariableAssignmentComponent::convertToMCFunctionCode(const string& destinationFilepath) {
	// TODO
	return "";
}

// TODO: OBSLUGA LICZB Z MINUSEM!!! (UJEMNYCH)

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
			if (!expectedOperator) throw createException("Expected operand here.");
			expectedOperator = false;
			break;
		case Token::TYPE_IDENTIFIER:
		case Token::TYPE_INTEGER_LITERAL:
			if (expectedOperator) throw createException("Expected operator here.");
			expectedOperator = true;
			containsOperand = true;
			break;
		case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
			if (expectedOperator) throw createException("Expected operator here but found opening parentheses.");
			parenthesesDepth++;
			break;
		case Token::TYPE_RIGHT_PARENTHESES_SEPARATOR:
			if (!expectedOperator) throw createException("Expected operand here but found closing parentheses.");
			if (parenthesesDepth == 0) throw createException("Unexpected redundant closing parentheses.");
			parenthesesDepth--;
			break;
		default:
			throw createException("Unexpected token type.");
		}
		index++;
		if (index == m_tokens.size()) throw createException("Expected semicolon but got end of file.");
	}
	if (!containsOperand) throw createException("Expression is expected to contain at least one operand.");
	if (!expectedOperator) throw createException("Expression must end with an operand rather than operator.");
}

shared_ptr<NumericValue> VariableAssignmentComponent::parseNumericValue(int& index) {
	shared_ptr<NumericValue> numericValue = make_shared<NumericValue>();
	NumericOperator lastOperator = NumericOperator::NONE;
	while (m_tokens[index].getType() != Token::TYPE_RIGHT_PARENTHESES_SEPARATOR &&
		m_tokens[index].getType() != Token::TYPE_SEMICOLON_SEPARATOR)
	{
		switch (m_tokens[index].getType()) {
		case Token::TYPE_PLUS_OPERATOR:
		case Token::TYPE_HYPHEN_OPERATOR:
		case Token::TYPE_ASTERISK_OPERATOR:
		case Token::TYPE_FORWARD_SLASH_OPERATOR:
			{
				NumericOperator thisOperator = readNumericValueOperator(index);
				NumericValue::Type valueType = numericValue->getNumericValueType();
				if (valueType == NumericValue::OPERATION_VALUE &&
					lastOperator != NumericOperator::NONE &&
					hasOperatorHigherPrecedence(thisOperator, lastOperator))
				{
					OperationValue lastOperation = dynamic_cast<OperationValue&>(*numericValue);
					shared_ptr<NumericValue> lowerPrecedenceOperand = lastOperation.leftOperand;
					shared_ptr<NumericValue> newOperationLeftOperand = lastOperation.rightOperand;
					shared_ptr<NumericValue> newOperationRightOperand = readOperandNumericValue(++index);
					shared_ptr<NumericValue> newOperation = make_shared<OperationValue>(newOperationLeftOperand, newOperationRightOperand, thisOperator);
					numericValue = make_shared<OperationValue>(lowerPrecedenceOperand, newOperation, lastOperator);
				} else {
					lastOperator = thisOperator;
				}
				break;
			}
		case Token::TYPE_IDENTIFIER:
		case Token::TYPE_INTEGER_LITERAL:
		case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
			{
				shared_ptr<NumericValue> operand = readOperandNumericValue(index);
				if (numericValue->getNumericValueType() == NumericValue::NONE) {
					numericValue = operand;
				} else {
					shared_ptr<NumericValue> operationValue = make_shared<OperationValue>(numericValue, operand, lastOperator);
					numericValue = operationValue;
				}
				break;
			}
		}
		index++;
	}
	//index++; // TODO: sprawdz czy potrzebne (ale raczej nie, bo generuje blad, kiedy odkomentowane)
	return tryToSimplifyNumericValue(numericValue);
}

shared_ptr<NumericValue> VariableAssignmentComponent::readOperandNumericValue(int& index) {
	switch (m_tokens[index].getType()) {
	case Token::TYPE_IDENTIFIER:
		return make_shared<IdentifierValue>(m_tokens[index].getValue());
	case Token::TYPE_INTEGER_LITERAL:
		return make_shared<LiteralIntegerValue>(stoi(m_tokens[index].getValue()));
	case Token::TYPE_LEFT_PARENTHESES_SEPARATOR:
		return parseNumericValue(++index);
	}
	throw createException("Internal error. Expected identifier, literal or opening parentheses here.");
}

NumericOperator VariableAssignmentComponent::readNumericValueOperator(int index) {
	switch (m_tokens[index].getType()) {
	case Token::TYPE_PLUS_OPERATOR: return NumericOperator::ADD;
	case Token::TYPE_HYPHEN_OPERATOR: return NumericOperator::SUBTRACT;
	case Token::TYPE_ASTERISK_OPERATOR: return NumericOperator::MULTIPLY;
	case Token::TYPE_FORWARD_SLASH_OPERATOR: return NumericOperator::DIVIDE;
	}
	throw createException("Internal error. Expected operator here.");
}

bool VariableAssignmentComponent::hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator) {
	int thisPrecedence = m_operatorsPrecedence.find(thisOperator)->second;
	int otherPrecedence = m_operatorsPrecedence.find(otherOperator)->second;
	return thisPrecedence > otherPrecedence;
}

shared_ptr<NumericValue> VariableAssignmentComponent::tryToSimplifyNumericValue(shared_ptr<NumericValue> numericValue) {
	if (numericValue->getNumericValueType() == NumericValue::OPERATION_VALUE) {
		OperationValue operationValue = dynamic_cast<OperationValue&>(*numericValue);
		auto operationValuePtr = make_shared<OperationValue>(operationValue);
		return tryToSimplifyOperationValue(operationValuePtr);
	}
	return numericValue;
}

shared_ptr<NumericValue> VariableAssignmentComponent::tryToSimplifyOperationValue(shared_ptr<OperationValue> operationValue) {
	operationValue->leftOperand = tryToSimplifyNumericValue(operationValue->leftOperand);
	operationValue->rightOperand = tryToSimplifyNumericValue(operationValue->rightOperand);
	if (operationValue->leftOperand->getNumericValueType() == NumericValue::LITERAL_INTEGER_VALUE &&
		operationValue->rightOperand->getNumericValueType() == NumericValue::LITERAL_INTEGER_VALUE)
	{
		int leftValue = dynamic_cast<LiteralIntegerValue&>(*operationValue->leftOperand).intValue;
		int rightValue = dynamic_cast<LiteralIntegerValue&>(*operationValue->rightOperand).intValue;
		switch (operationValue->numericOperator) {
		case NumericOperator::ADD: return make_shared<LiteralIntegerValue>(leftValue + rightValue);
		case NumericOperator::SUBTRACT: return make_shared<LiteralIntegerValue>(leftValue - rightValue);
		case NumericOperator::MULTIPLY: return make_shared<LiteralIntegerValue>(leftValue * rightValue);
		case NumericOperator::DIVIDE: return make_shared<LiteralIntegerValue>(leftValue / rightValue);
		}
	}
	return operationValue;
}
