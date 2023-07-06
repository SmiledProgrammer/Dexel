#ifndef NUMERIC_VALUES_TEST_H
#define NUMERIC_VALUES_TEST_H

#include <vector>
#include "../main/dexel/NumericValues.h"

using namespace std;

namespace dexel {

	class NumericValuesTest {
	public:
		struct TestCase {
			string code;
			string expectedNumericExpressionString;

			TestCase(const string& code, const string& expectedNumericExpressionString)
				: code(code), expectedNumericExpressionString(expectedNumericExpressionString) {}
		};

	private:
		vector<TestCase> m_testCases;

	public:
		NumericValuesTest();

		int runTests();

	private:
		void displayFailInfo(const string& expectedString, const string& actualString);
		string numericValueToNumericExpressionString(NumericValue& numericValue);

	};
}

#endif
