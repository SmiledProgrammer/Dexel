#ifndef SYNTAX_COMPONENT_H
#define SYNTAX_COMPONENT_H

#include <vector>
#include <memory>
#include "Token.h"
#include "ParsingException.h"

namespace dexel {

	class SyntaxComponent {
	protected:
		vector<Token>& m_tokens;
		int m_index;

		static string m_outputFunctionsDirectoryPath;
		static bool m_overrideFiles;

	protected:
		SyntaxComponent(vector<Token>& tokens, int index);

	public:
		virtual void readComponent();
		virtual string convertToMCFunctionCode(const string& functionNamePrefix);

		static void setGlobalSettings(const string& destinationDirectoryPath, bool overrideFiles);

		inline int getCurrentIndex() const { return m_index; }

	protected:
		Token getNextToken();
		vector<shared_ptr<SyntaxComponent>> readComponentsBlock();
		string convertComponentsBlockToMCFunctionCode(const string& functionName, const vector<shared_ptr<SyntaxComponent>>& componentsBlock);
		void checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes);
		void createMCFunctionFile(const string& functionName, const string& dexelCode);
		
	private:
		shared_ptr<SyntaxComponent> createComponentFromNextToken();

	protected:
		ParsingException createException(const string& message);

	};
}

#endif
