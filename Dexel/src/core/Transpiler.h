#ifndef DEXEL_TRANSPILER_H
#define DEXEL_TRANSPILER_H

#include <string>
#include <filesystem>

using namespace std;

namespace dexel {

	/**
	 * \brief Klasa wczytująca opcje transpilacji.
	 *
	 * Klasa służąca do sprawdzenia poprawności i wczytania opcji transpilacji.
	 */
	class Transpiler {

		string m_sourceFile = "";
		string m_destinationDirectory = filesystem::current_path().string();
		bool m_overrideDirectories = true;
		bool m_nativeCommands = false;

	public:
		/**
		 * \brief Funkcja wczytująca opcje transpilacji.
		 *
		 * Funkcja walidująca i zapisująca opcje transpilacji..
		 *
		 * \param argc - Ilość argumentów wejściowych programu.
		 * \param argv - Tablica argumentów wejściowych programu.
		 * \return Ilość poprawnie wczytanych opcji transpilacji.
		 */
		int parseArguments(int argc, char** argv);

		inline const string& const getSourceFile() { return m_sourceFile; }
		inline const string& const getDestinationDirectory() { return m_destinationDirectory; }
		inline bool const getOverrideDirectories() { return m_overrideDirectories; }

	private:
		int printError(int errorCode);

	};
}

#endif
