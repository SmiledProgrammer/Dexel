#ifndef VARIABLE_ASSIGNMENT_COMPONENT_H
#define VARIABLE_ASSIGNMENT_COMPONENT_H

#include <map>
#include <memory>
#include "SyntaxComponent.h"
#include "NumericValues.h"

namespace dexel {

	class VariableAssignmentComponent : public SyntaxComponent {

		struct NumericValueConversionResult {
			string code;
			string outcomeScoreLocation;

			NumericValueConversionResult(const string& code, const string& outcomeScoreLocation)
				: code(code), outcomeScoreLocation(outcomeScoreLocation) {}
		};

		static const vector<Token::Type> m_startingPattern;
		static const map<NumericOperator, int> m_operatorsPrecedence;

		string m_variableName;
		shared_ptr<NumericValue> m_numericValue;
		int m_numericValueConversionCounter;

	public:
		VariableAssignmentComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

		bool isAssignmentExpressionValid();
		shared_ptr<NumericValue> parseNumericValue(int& startingTokenIndex);

	private:
		shared_ptr<NumericValue> readOperandNumericValue(int& index);
		NumericOperator readNumericValueOperator(int index);
		bool hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator);
		shared_ptr<NumericValue> tryToSimplifyNumericValue(shared_ptr<NumericValue> numericValue);
		shared_ptr<NumericValue> tryToSimplifyOperationValue(shared_ptr<OperationValue> operationValue);
		NumericValueConversionResult convertNumericValueToMCFunctionCode(shared_ptr<NumericValue> numericValue);
		string getNextNumericValueConversionIdentifier();
		string getOperatorString(NumericOperator numericOperator);

	};
}

#endif
