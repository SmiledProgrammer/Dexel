#ifndef CONDITION_COMPONENT_H
#define CONDITION_COMPONENT_H

#include <list>
#include "SyntaxComponent.h"

namespace dexel {

	class ConditionComponent : public SyntaxComponent {

		struct ConditionBlock {
			string condition;
			vector<SyntaxComponent> insideComponents;

			ConditionBlock(const string& condition, const vector<SyntaxComponent>& insideBlockComponents)
				: condition(condition), insideComponents(insideBlockComponents) {}
		};

		vector<ConditionBlock> m_conditionBlocks;

	public:
		ConditionComponent(vector<Token>& tokens, int index);

		bool readComponent() override;
		string convertToMCFunctionCode(const string& destinationFilepath) override;

	private:
		string readCondition();

	};
}

#endif
