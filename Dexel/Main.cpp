#include "Transpiler.h"

using namespace dexel;

int main(int argc, char** argv) {
	Transpiler transpiler = Transpiler();
	int result = transpiler.parseArguments(argc, argv);

	return result;
}
