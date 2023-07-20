#ifndef CONDITION_COMPONENT_H
#define CONDITION_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący ciąg instrukcji warunkowych.
	 *
	 * Klasa służąca do parsowania i generowania kodu odpowiadającego za ciąg instrukcji warunkowych.
	 */
	class ConditionComponent : public SyntaxComponent {

		static const vector<Token::Type> m_ifBlockStartingPattern;
		static const vector<Token::Type> m_elseIfBlockStartingPattern;

		static int m_mcFunctionConditionCounter;

		struct ConditionBlock {
			string condition;
			vector<shared_ptr<SyntaxComponent>> insideComponents;

			ConditionBlock(const string& condition, const vector<shared_ptr<SyntaxComponent>>& insideBlockComponents)
				: condition(condition), insideComponents(insideBlockComponents) {}
		};

		vector<ConditionBlock> m_conditionBlocks;

	public:
		ConditionComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

	private:
		static string getNextConditionFunctionName(const string& functionNamePrefix);

	};
}

#endif
