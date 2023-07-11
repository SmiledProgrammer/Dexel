#ifndef NUMERIC_VALUES_H
#define NUMERIC_VALUES_H

#include <string>
#include <memory>

using namespace std;

namespace dexel {

	enum NumericOperator {
		NONE,
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

		virtual Type getNumericValueType() const {
			return NONE;
		}

		virtual string toString() const {
			return "Generic NumericValue";
		}
	};

	struct OperationValue : public NumericValue {

		shared_ptr<NumericValue> leftOperand;
		shared_ptr<NumericValue> rightOperand;
		NumericOperator numericOperator;

		OperationValue(shared_ptr<NumericValue> leftOperand, shared_ptr<NumericValue> rightOperand, NumericOperator numericOperator)
			: leftOperand(leftOperand), rightOperand(rightOperand), numericOperator(numericOperator) {}

		Type getNumericValueType() const override {
			return OPERATION_VALUE;
		}

		string toString() const override {
			char operatorSymbol = ' ';
			switch (numericOperator) {
			case NumericOperator::ADD: operatorSymbol = '+'; break;
			case NumericOperator::SUBTRACT: operatorSymbol = '-'; break;
			case NumericOperator::MULTIPLY: operatorSymbol = '*'; break;
			case NumericOperator::DIVIDE: operatorSymbol = '/'; break;
			}
			return "OperationValue: " + leftOperand->toString() + " " + operatorSymbol + " " + rightOperand->toString();
		}
	};

	struct IdentifierValue : public NumericValue {
		string identifier;

		IdentifierValue(string identifier)
			: identifier(identifier) {}

		Type getNumericValueType() const override {
			return IDENTIFIER_VALUE;
		}

		string toString() const override {
			return "IdentifierValue: " + identifier;
		}
	};

	struct LiteralIntegerValue : public NumericValue {
		int intValue;

		LiteralIntegerValue(int intValue)
			: intValue(intValue) {}

		Type getNumericValueType() const override {
			return LITERAL_INTEGER_VALUE;
		}

		string toString() const override {
			return "LiteralIntegerValue: " + intValue;
		}
	};
}

#endif
