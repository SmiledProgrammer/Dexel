#ifndef VARIABLE_ASSIGNMENT_COMPONENT_H
#define VARIABLE_ASSIGNMENT_COMPONENT_H

#include <map>
#include <memory>
#include "SyntaxComponent.h"
#include "NumericValues.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący przypisanie wartości do zmiennej.
	 *
	 * Klasa służąca do parsowania i generowania kodu odpowiadającego za przypisanie wartości do zmiennej.
	 */
	class VariableAssignmentComponent : public SyntaxComponent {

		/**
		 * \brief Wynik konwersji wartości numerycznej.
		 *
		 * Struktura wspomagająca generowanie kodu przypisywania wartości zmiennej w języku MCFunction.
		 */
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

		/**
		 * \brief Funkcja sprawdzająca strukturę przypisania wartości numerycznej.
		 *
		 * Funkcja wspomagająca proces parsowania kodu przypisania wartości numerycznej poprzez sprawdzenie poprawności struktury wyrażenia numerycznego.
		 * 
		 * \return Czy struktura jest poprawna.
		 */
		bool isAssignmentExpressionValid();

		/**
		 * \brief Funkcja parsująca kod przypisania wartości numerycznej.
		 *
		 * Funkcja parsująca kod przypisania wartości numerycznej poprzez zamianę tokenów kodu utworzenia wartości numerycznej na drzewiastą strukturę operacji numerycznych.
		 *
		 * \param startingTokenIndex - Indeks pierwszego tokena rozpatrywanego w danym wywołaniu.
		 * \return Wyrażenie numeryczne (wyrażona w drzewiastej strukturze wartości numerycznych).
		 */
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
