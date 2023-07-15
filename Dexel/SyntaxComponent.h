#ifndef SYNTAX_COMPONENT_H
#define SYNTAX_COMPONENT_H

#include <vector>
#include "Token.h"
#include "ParsingException.h"

namespace dexel {

	class SyntaxComponent {
	protected:
		vector<Token>& m_tokens;
		int m_index;

		static string m_destinationDirectoryPath;

	protected:
		SyntaxComponent(vector<Token>& tokens, int index);

	public:
		virtual void readComponent();
		virtual string convertToMCFunctionCode(const string& destinationFilepath); // TODO: sprawdz czy ten parametr jest potrzebny

		static void setGlobalDestinationDirectoryPath(const string& dirPath);

		inline int getCurrentIndex() const { return m_index; }

	protected:
		Token getNextToken();
		vector<SyntaxComponent> readComponentsBlock();
		void checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes);
		void createMCFunctionFile(const string& functionName, const string& dexelCode);
		
	private:
		SyntaxComponent createComponentFromNextToken();

	protected:
		ParsingException createException(const string& message);

	};
}

#endif
