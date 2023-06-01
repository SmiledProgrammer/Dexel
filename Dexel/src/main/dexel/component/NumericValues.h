#ifndef NUMERIC_VALUES_H
#define NUMERIC_VALUES_H

#include <string>

using namespace std;

namespace dexel {

	enum NumericOperator {
		ADD,
		SUBTRACT,
		MULTIPLY,
		DIVIDE
	};

	struct NumericValue {
		static enum Type {
			OPERATION_VALUE,
			IDENTIFIER_VALUE,
			LITERAL_INTEGER_VALUE
		};

		virtual Type getNumericValueType() {
			throw "Cannot get proper numeric value type";
		}
	};

	struct OperationValue : public NumericValue {

		NumericValue leftOperand;
		NumericValue rightOperand;
		NumericOperator numericOperator;

		OperationValue(NumericValue leftOperand, NumericValue rightOperand, NumericOperator numericOperator)
			: leftOperand(leftOperand), rightOperand(rightOperand), numericOperator(numericOperator) {}

		Type getNumericValueType() override {
			return OPERATION_VALUE;
		}
	};

	struct IdentifierValue : public NumericValue {
		string identifier;

		IdentifierValue(string identifier)
			: identifier(identifier) {}

		Type getNumericValueType() override {
			return IDENTIFIER_VALUE;
		}
	};

	struct LiteralIntegerValue : public NumericValue {
		int intValue;

		LiteralIntegerValue(int intValue)
			: intValue(intValue) {}

		Type getNumericValueType() override {
			return LITERAL_INTEGER_VALUE;
		}
	};

	NumericValue tryToSimplifyOperationValue(OperationValue operationValue) {
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
}

#endif
