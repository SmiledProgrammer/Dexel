#ifndef SYNTAX_COMPONENT_H
#define SYNTAX_COMPONENT_H

#include <vector>
#include "../Token.h"

namespace dexel {

	class SyntaxComponent {
	protected:
		vector<Token>& m_tokens;
		int m_index;

		static string m_destinationDirectoryPath;

	protected:
		SyntaxComponent(vector<Token>& tokens, int index);

	public:
		virtual bool readComponent();
		virtual string convertToMCFunctionCode(const string& destinationFilepath);

		static void setGlobalDestinationDirectoryPath(const string& dirPath);

	protected:
		Token getNextToken();
		vector<SyntaxComponent> readComponentsBlock();
		bool checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes);
		void createMCFunctionFile(const string& functionName, const string& dexelCode);
		
	private:
		SyntaxComponent createComponentFromToken(Token token);

	};
}

#endif
