#ifndef VARIABLE_ASSIGNMENT_COMPONENT_H
#define VARIABLE_ASSIGNMENT_COMPONENT_H

#include <map>
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
		NumericValue parseNumericValue(int& startingTokenIndex);

	private:
		NumericValue readOperandNumericValue(int& index);
		NumericOperator readNumericValueOperator(int index);
		bool hasOperatorHigherPrecedence(NumericOperator thisOperator, NumericOperator otherOperator);
		NumericValue tryToSimplifyNumericValue(NumericValue numericValue);
		NumericValue tryToSimplifyOperationValue(OperationValue operationValue);

	};
}

#endif
