// Can only be used in one test file. Do not copy!!
#define DOCTEST_CONFIG_IMPLEMENT

#include "TestHeader.hpp"

#include <string>
#include <vector>

int doctest_run(const int argc, const char *const *argv) {
	doctest::Context context;
	context.applyCommandLine(argc, argv);
	int res = context.run();

	return res;
}