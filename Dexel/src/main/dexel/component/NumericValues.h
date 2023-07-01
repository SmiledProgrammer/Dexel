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
			NONE,
			OPERATION_VALUE,
			IDENTIFIER_VALUE,
			LITERAL_INTEGER_VALUE
		};

		virtual Type getNumericValueType() {
			return NONE;
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
}

#endif
