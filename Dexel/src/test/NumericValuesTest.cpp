#include "NumericValuesTest.h"

#include <iostream>
#include <map>
#include "../main/dexel/Lexer.h"
#include "../main/dexel/VariableAssignmentComponent.h"

using namespace dexel;
using namespace std;

const map<NumericOperator, string> operatorSymbols{
	{ NumericOperator::ADD, "+"},
	{ NumericOperator::SUBTRACT, "-" },
	{ NumericOperator::MULTIPLY, "*" },
	{ NumericOperator::DIVIDE, "/"},
};

NumericValuesTest::NumericValuesTest() {
	m_testCases = {
		TestCase("3;", "3"),
		TestCase("b;", "b"),
		TestCase("3 + 5;", "(3 + 5)"),
		TestCase("b + 3;", "(b + 3)"),
		TestCase("3 + b;", "(3 + b)"),
		TestCase("(4 + 9);", "(4 + 9)"),
		TestCase("(7 + b);", "(7 + b)")
	};
}

int NumericValuesTest::runTests() {
	int failedTestsCount = 0;
	for (TestCase testCase : m_testCases) {
		Lexer lexer(testCase.code);
		vector<Token> tokens = lexer.tokenize();
		int startingIndex = 0;
		try {
			VariableAssignmentComponent component(tokens, startingIndex);
			NumericValue actualNumericValue = component.parseNumericValue(startingIndex);
			string actualString = numericValueToNumericExpressionString(actualNumericValue);
			if (testCase.expectedNumericExpressionString != actualString) {
				displayFailInfo(testCase.expectedNumericExpressionString, actualString);
			}
		} catch (string ex) {
			string actualString = "Exception: " + ex;
			displayFailInfo(testCase.expectedNumericExpressionString, actualString);
		}
	}
	cout << "Numeric values tests run. Failed tests count: " << failedTestsCount << endl;
	return failedTestsCount;
}

void NumericValuesTest::displayFailInfo(const string& expectedString, const string& actualString) {
	cout << "Test failed - expected expression string:" << endl;
	cout << expectedString << endl;
	cout << "but actually got:" << endl;
	cout << actualString << endl;
}

string NumericValuesTest::numericValueToNumericExpressionString(NumericValue& numericValue) {
	switch (numericValue.getNumericValueType()) {
	case NumericValue::LITERAL_INTEGER_VALUE:
		return to_string(dynamic_cast<LiteralIntegerValue&>(numericValue).intValue);
	case NumericValue::IDENTIFIER_VALUE:
		return dynamic_cast<IdentifierValue&>(numericValue).identifier;
	case NumericValue::OPERATION_VALUE:
		OperationValue operationValue = dynamic_cast<OperationValue&>(numericValue);
		string operatorSymbol = operatorSymbols.find(operationValue.numericOperator)->second;
		string leftOperandString = numericValueToNumericExpressionString(operationValue.leftOperand);
		string rightOperandString = numericValueToNumericExpressionString(operationValue.rightOperand);
		return "(" + leftOperandString + " " + operatorSymbol + " " + rightOperandString + ")";
	}
	return "";
}
