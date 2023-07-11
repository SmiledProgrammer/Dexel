#ifndef VARIABLE_ASSIGNMENT_COMPONENT_H
#define VARIABLE_ASSIGNMENT_COMPONENT_H

#include <map>
#include <memory>
#include "SyntaxComponent.h"
#include "NumericValues.h"

namespace dexel {

	class VariableAssignmentComponent : public SyntaxComponent {

		static const vector<Token::Type> m_startingPattern;
		static const map<NumericOperator, int> m_operatorsPrecedence;

		string m_variableName;
		NumericValue m_numericValue;

	public:
		VariableAssignmentComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

		bool isAssignmentExpressionValid();
		shared_ptr<NumericValue> parseNumericValue(int& startingTokenIndex);

	private:
		shared_ptr<NumericValue> readOperandNumericValue(int& index);
		NumericOperator readNumericValueOperator(int index);
		bool hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator);
		shared_ptr<NumericValue> tryToSimplifyNumericValue(shared_ptr<NumericValue> numericValue);
		shared_ptr<NumericValue> tryToSimplifyOperationValue(shared_ptr<OperationValue> operationValue);

	};
}

#endif
