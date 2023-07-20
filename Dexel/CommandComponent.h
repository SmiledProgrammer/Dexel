#ifndef COMMAND_COMPONENT_H
#define COMMAND_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący użycie komendy.
	 * 
	 * Klasa służąca do parsowania i generowania kodu odpowiadającego za użycie komendy z języka MCFunction.
	 */
	class CommandComponent : public SyntaxComponent {

		static const vector<Token::Type> m_commandExpressionPattern;

		string m_commandExpression;

	public:
		CommandComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

	};
}

#endif
