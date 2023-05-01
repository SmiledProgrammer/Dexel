#ifndef FUNCTION_DEFINITION_COMPONENT_H
#define FUNCTION_DEFINITION_COMPONENT_H

#include <vector>
#include "SyntaxComponent.h"

namespace dexel {

	class FunctionDefinitionComponent : public SyntaxComponent {

		vector<SyntaxComponent> m_insideFuncionComponents;

	public:

		FunctionDefinitionComponent(vector<Token>& tokens, int index);

		// TODO

	};
}

#endif
