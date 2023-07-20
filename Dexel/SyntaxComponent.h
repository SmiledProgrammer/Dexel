#ifndef SYNTAX_COMPONENT_H
#define SYNTAX_COMPONENT_H

#include <vector>
#include <memory>
#include "Token.h"
#include "ParsingException.h"

namespace dexel {

	/**
	 * \brief Bazowy komponent parsera.
	 *
	 * Klasa bazowa dla komponentów parsera służących do parsowania i generowania kodu w języku MCFunction.
	 */
	class SyntaxComponent {
	protected:
		vector<Token>& m_tokens;
		int m_index;

		static string m_outputFunctionsDirectoryPath;
		static bool m_overrideFiles;

	protected:
		SyntaxComponent(vector<Token>& tokens, int index);

	public:
		/**
		 * \brief Funkcja wczytująca komponent kodu.
		 *
		 * Funkcja parsująca kod poprzez wczytanie tokenów do zmiennych właściwych dla danego rodzaju komponentu.
		 */
		virtual void readComponent();

		/**
		 * \brief Funkcja generująca kod języka MCFunction.
		 *
		 * Funkcja konwertująca dane danego komponentu na kod oraz generująca odpowiednie pliki języka MCFunction.
		 *
		 * \param functionNamePrefix - Prefiks nazwy ewentualnie generowanych plików funkcji języka MCFunction.
		 * \return Wygenerowany kod języka MCFunction.
		 */
		virtual string convertToMCFunctionCode(const string& functionNamePrefix);

		/**
		 * \brief Funkcja ustawień dla parsowania komponentów.
		 *
		 * Funkcja ustawiająca globalne ustawienia dla parsowania komponentów kodu.
		 *
		 * \param destinationDirectoryPath - Ścieżka folderu do generowania plików wyjściowych.
		 * \param overrideFiles - Czy nadpisywać istniejące już pliki i foldery.
		 */
		static void setGlobalSettings(const string& destinationDirectoryPath, bool overrideFiles);

		/**
		 * \brief Funkcja zwracająca indeks aktualnego tokena.
		 *
		 * Funkcja zwracająca indeks aktualnego tokena.
		 *
		 * \return Indeks aktualnego tokena.
		 */
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
