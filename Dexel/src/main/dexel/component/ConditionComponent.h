#ifndef CONDITION_COMPONENT_H
#define CONDITION_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	class ConditionComponent : public SyntaxComponent {

		static const vector<Token::Type> m_ifBlockStartingPattern;
		static const vector<Token::Type> m_elseIfBlockStartingPattern;

		struct ConditionBlock {
			string condition;
			vector<SyntaxComponent> insideComponents;

			ConditionBlock(const string& condition, const vector<SyntaxComponent>& insideBlockComponents)
				: condition(condition), insideComponents(insideBlockComponents) {}
		};

		vector<ConditionBlock> m_conditionBlocks;

	public:
		ConditionComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

	};
}

#endif
