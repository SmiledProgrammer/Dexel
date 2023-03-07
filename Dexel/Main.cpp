#include "DexelTranspiler.h"

int main(int argc, char** argv) {
	DexelTranspiler transpiler = DexelTranspiler();
	int result = transpiler.parseArguments(argc, argv);

	return result;
}
