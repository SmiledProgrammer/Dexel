#ifndef DATAPACK_GENERATOR_H
#define DATAPACK_GENERATOR_H

#include <string>
#include "DexelFileSyntaxComponent.h"

using namespace std;

namespace dexel {


	/**
	 * \brief Klasa do generowania paczek zasobów.
	 *
	 * Klasa służąca do generowania od początku paczki zasobów.
	 */
	class DatapackGenerator {

		string m_destinationDirectory;
		bool m_overrideDirectories;

	public:
		DatapackGenerator(const string& destinationDirectory, bool overrideDirectories);

		/**
		 * \brief Funkcja generująca paczkę zasobów.
		 *
		 * Funkcja generująca od początku całą paczkę zasobów.
		 *
		 * \param components - Komponenty plików języka Dexel będące wynikiem parsowania.
		 */
		void generateDatapack(const vector<DexelFileSyntaxComponent>& components);

	private:
		void generateEmptyDatapack();
		void generateDefaultInitFunction();
		void generateMCFunctionFiles(const vector<DexelFileSyntaxComponent>& components);

		void createPackMCMetaFile(const string& pathStr);

	};
}

#endif
