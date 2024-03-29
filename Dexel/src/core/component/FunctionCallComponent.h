﻿#ifndef FUNCTION_CALL_COMPONENT_H
#define FUNCTION_CALL_COMPONENT_H

#include "SyntaxComponent.h"

namespace dexel {

	/**
	 * \brief Komponent parsera obsługujący wywołanie funkcji.
	 *
	 * Klasa służąca do parsowania i generowania kodu odpowiadającego za wywołanie funkcji.
	 */
	class FunctionCallComponent : public SyntaxComponent {

		static const vector<Token::Type> m_functionCallPattern;

		string m_functionName;

	public:
		FunctionCallComponent(vector<Token>& tokens, int index);

		void readComponent() override;
		string convertToMCFunctionCode(const string& functionNamePrefix) override;

	};
}

#endif
