#ifndef DEXEL_FILE_SYNTAX_COMPONENT_H
#define DEXEL_FILE_SYNTAX_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	class DexelFileSyntaxComponent : public SyntaxComponent {

		string m_filepath;
		vector<SyntaxComponent> m_components;

	public:
		DexelFileSyntaxComponent(vector<Token>& tokens, const string& filepath);

		bool readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

		inline const string& getFilepath() const { return m_filepath; }
		inline const vector<SyntaxComponent>& getComponents() const { return m_components; }

	};
}

#endif
