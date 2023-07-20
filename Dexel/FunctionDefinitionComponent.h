#ifndef FUNCTION_DEFINITION_COMPONENT_H
#define FUNCTION_DEFINITION_COMPONENT_H

#include <vector>
#include "SyntaxComponent.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący definiowanie funkcji.
	 *
	 * Klasa służąca do parsowania i generowania kodu odpowiadającego za zdefiniowanie funkcji.
	 */
	class FunctionDefinitionComponent : public SyntaxComponent {

		string m_functionName;
		vector<shared_ptr<SyntaxComponent>> m_insideFunctionComponents;

		static const vector<Token::Type> m_startingPattern;

	public:
		FunctionDefinitionComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

	};
}

#endif
