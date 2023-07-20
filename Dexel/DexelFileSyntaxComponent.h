#ifndef DEXEL_FILE_SYNTAX_COMPONENT_H
#define DEXEL_FILE_SYNTAX_COMPONENT_H

#include "FunctionDefinitionComponent.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący plik języka Dexel.
	 *
	 * Klasa służąca do parsowania i generowania kodu danego pliku źródłowego w języku Dexel.
	 */
	class DexelFileSyntaxComponent : public SyntaxComponent {

		string m_filepath;
		vector<FunctionDefinitionComponent> m_components;

	public:
		DexelFileSyntaxComponent(vector<Token>& tokens, const string& filepath);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

		inline const string& getFilepath() const { return m_filepath; }

	};
}

#endif
