#include "StringUtilsTest.h"

#include <iostream>
#include "../core/StringUtils.h"

using namespace dexel;
using namespace std;

StringUtilsTest::StringUtilsTest() {
	m_testCases = {
		TestCase("dummy", "dummy"),
		TestCase("\t\t abc", "\t\t abc"),
		TestCase("abc\n", "abc"),
		TestCase("TEST\n\n\n", "TEST"),
		TestCase("Polish   ", "Polish   "),
		TestCase("works\n  ", "works"),
		TestCase("animals\n friends", "animalsfriends"),
		TestCase("animals \n friends", "animals friends"),
		TestCase("TAB\t\n\t \tanother", "TAB\tanother"),
		TestCase("double \n kill \n death...", "double kill death..."),
		TestCase("\nstart", "start"),
		TestCase("\n  \tstart2", "start2"),
		TestCase("\n start\t\n nooo", "start\tnooo")
	};
}

int StringUtilsTest::runTests() {
	int failedTestsCount = 0;
	for (TestCase testCase : m_testCases) {
		string actualString = removeNewlines(testCase.code);
		if (testCase.expectedString != actualString) {
			displayFailInfo(testCase.expectedString, actualString);
			failedTestsCount++;
		}
	}
	cout << "String utils tests run. Failed tests count: " << failedTestsCount << endl;
	return failedTestsCount;
}

void StringUtilsTest::displayFailInfo(const string& expectedString, const string& actualString) {
	string e = convertSpecialSymbolsToText(expectedString);
	string a = convertSpecialSymbolsToText(actualString);
	cout << "Test failed - expected string:" << endl;
	cout << convertSpecialSymbolsToText(expectedString) << endl;
	cout << "but actually got:" << endl;
	cout << convertSpecialSymbolsToText(actualString) << endl;
	cout << endl;
}

string StringUtilsTest::convertSpecialSymbolsToText(const string& str) {
	string result = "";
	for (int i = 0; i < str.length(); i++) {
		switch (str[i]) {
		case '\n': result += "\\n"; break;
		case '\t': result += "\\t"; break;
		default: result += str[i];
		}
	}
	return result;
}
