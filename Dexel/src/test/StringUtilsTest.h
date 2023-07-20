#ifndef STRING_UTILS_TEST_H
#define STRING_UTILS_TEST_H

#include <string>
#include <vector>

using namespace std;

namespace dexel {

	/**
	 * \brief Klasa testów tekstowych funkcji pomocniczych.
	 *
	 * Klasa testowa do przeprowadzania testów tekstowych funkcji pomocniczych.
	 */
	class StringUtilsTest {
	public:
		struct TestCase {
			string code;
			string expectedString;

			TestCase(const string& code, const string& expectedString)
				: code(code), expectedString(expectedString) {}
		};

	private:
		vector<TestCase> m_testCases;

	public:
		StringUtilsTest();

		int runTests();

	private:
		void displayFailInfo(const string& expectedString, const string& actualString);
		string convertSpecialSymbolsToText(const string& str);

	};
}

#endif
