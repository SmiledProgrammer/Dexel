#include "NumericValuesTest.h"

#include <iostream>
#include <map>
#include "Lexer.h"
#include "VariableAssignmentComponent.h"
#include "ParsingException.h"

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
		TestCase("3 + 5;", "8"),
		TestCase("b + 3;", "(b + 3)"),
		TestCase("3 + b;", "(3 + b)"),
		TestCase("(4 + 9);", "13"),
		TestCase("(7 + b);", "(7 + b)"),
		TestCase("(b * c);", "(b * c)"),
		TestCase("(c / b);", "(c / b)"),
		TestCase("(c - b);", "(c - b)"),
		TestCase("(a + b + c);", "((a + b) + c)"),
		TestCase("a * b + c;", "((a * b) + c)"),
		TestCase("(a + b * c);", "(a + (b * c))"),
		TestCase("a - b / c;", "(a - (b / c))"),
		TestCase("a * (b + c);", "(a * (b + c))"),
		TestCase("(a - b) / c;", "((a - b) / c)"),
		TestCase("(a + b) * (c - a);", "((a + b) * (c - a))"),
		TestCase("a + 33 * c / (((d - e) + f) + 3 * 40) - g;", "((a + ((33 * c) / (((d - e) + f) + 120))) - g)"),
		TestCase("15 - 30 / 5 * 7 * (250 - 130);", "-5025"),
		TestCase("(((a + 8) * 16 - 4) + 3 / 3) * (17 + 4);", "(((((a + 8) * 16) - 4) + 1) * 21)")
	};
}

int NumericValuesTest::runTests() {
	int failedTestsCount = 0;
	for (TestCase testCase : m_testCases) {
		Lexer lexer(testCase.code, "test");
		vector<Token> tokens = lexer.tokenize();
		int startingIndex = 0;
		try {
			VariableAssignmentComponent component(tokens, startingIndex);
			shared_ptr<NumericValue> actualNumericValue = component.parseNumericValue(startingIndex);
			string actualString = numericValueToNumericExpressionString(actualNumericValue);
			if (testCase.expectedNumericExpressionString != actualString) {
				displayFailInfo(testCase.expectedNumericExpressionString, actualString);
				failedTestsCount++;
			}
		} catch (ParsingException ex) {
			string actualString = "Exception: " + ex.getMessage();
			displayFailInfo(testCase.expectedNumericExpressionString, actualString);
			failedTestsCount++;
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
	cout << endl;
}

string NumericValuesTest::numericValueToNumericExpressionString(shared_ptr<NumericValue> numericValue) {
	switch (numericValue->getNumericValueType()) {
	case NumericValue::LITERAL_INTEGER_VALUE:
		return to_string(dynamic_cast<LiteralIntegerValue&>(*numericValue).intValue);
	case NumericValue::IDENTIFIER_VALUE:
		return dynamic_cast<IdentifierValue&>(*numericValue).identifier;
	case NumericValue::OPERATION_VALUE:
		OperationValue operationValue = dynamic_cast<OperationValue&>(*numericValue);
		string operatorSymbol = operatorSymbols.find(operationValue.numericOperator)->second;
		string leftOperandString = numericValueToNumericExpressionString(operationValue.leftOperand);
		string rightOperandString = numericValueToNumericExpressionString(operationValue.rightOperand);
		return "(" + leftOperandString + " " + operatorSymbol + " " + rightOperandString + ")";
	}
	return "";
}
