#ifndef DEXEL_FILE_SYNTAX_COMPONENT_H
#define DEXEL_FILE_SYNTAX_COMPONENT_H

#include "FunctionDefinitionComponent.h"

namespace dexel {

	class DexelFileSyntaxComponent : public SyntaxComponent {

		string m_filepath;
		vector<FunctionDefinitionComponent> m_components;

	public:
		DexelFileSyntaxComponent(vector<Token>& tokens, const string& filepath);

		void readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

		inline const string& getFilepath() const { return m_filepath; }

	};
}

#endif
