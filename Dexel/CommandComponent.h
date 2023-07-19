#ifndef COMMAND_COMPONENT_H
#define COMMAND_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

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
