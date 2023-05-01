#ifndef COMMAND_COMPONENT_H
#define COMMAND_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	class CommandComponent : public SyntaxComponent {

		string m_commandExpression;

	public:
		CommandComponent(vector<Token>& tokens, int index);

		bool readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

	};
}

#endif
