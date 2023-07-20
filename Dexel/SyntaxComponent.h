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
		/**
		 * \brief Funkcja pobierająca kolejny token.
		 *
		 * Funkcja przesuwająca indeks i zwracająca kolejny analizowany token.
		 *
		 * \return Kolejny token.
		 */
		Token getNextToken();

		/**
		 * \brief Funkcja wczytująca blok komponentów.
		 *
		 * Funkcja wczytująca komponenty bloku kodu języka Dexel (fragmentu kodu pomiędzy dwiema klamerkami {}).
		 *
		 * \return Wskaźniki na wczytane komponenty.
		 */
		vector<shared_ptr<SyntaxComponent>> readComponentsBlock();

		/**
		 * \brief Funkcja generująca kod z bloku komponentów.
		 *
		 * Funkcja generująca kod jezyka MCFunction na podstawie bloku komponentów.
		 *
		 * \param functionName - Nazwa funkcji, w której znajduje się blok komponentów.
		 * \param componentsBlock - Blok komponentów.
		 * \return Wygenerowany kod języka MCFunction.
		 */
		string convertComponentsBlockToMCFunctionCode(const string& functionName, const vector<shared_ptr<SyntaxComponent>>& componentsBlock);

		/**
		 * \brief Funkcja sprawdzająca typy następnych tokenów.
		 *
		 * Funkcja sprawdzająca czy ciąg typów następnych tokenów jest zgodny z podanym wektorem tokenów, a w przeciwnym razie rzucająca stosowny wyjątek.
		 *
		 * \param nextTokensTypes - Wektor oczekiwanych typów następnych tokenów.
		 */
		void checkNextTokensTypes(const vector<Token::Type>& nextTokensTypes);

		/**
		 * \brief Funkcja tworząca funkcję MCFunction.
		 *
		 * Funkcja tworząca plik kodu źródłowego języka MCFunction.
		 *
		 * \param functionName - Nazwa tworzonej funkcji.
		 * \param dexelCode - Kod źródłowy do umieszczenia w pliku.
		 */
		void createMCFunctionFile(const string& functionName, const string& dexelCode);
		
	private:
		shared_ptr<SyntaxComponent> createComponentFromNextToken();

	protected:
		/**
		 * \brief Funkcja tworząca wyjątek parsowania.
		 *
		 * Funkcja pomocnicza służąca do tworzenia wyjątków parsowania z odpowiednio wypełnionymi informacjami o położeniu i przyczynie wystąpienia wyjątku.
		 *
		 * \param message - Komunikat wyjątku.
		 * \return Obiekt zawierający wszystkie informacje o wyjątku.
		 */
		ParsingException<string> createException(const string& message);

	};
}

#endif
