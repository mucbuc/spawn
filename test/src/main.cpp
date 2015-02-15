#include <iostream>
#include <functional>
#include <string>
#include <tuple>

#include "../plank/src/test.h"
#include "src/object.h"
#include "src/abstract.h"

int main(int argc, const char * argv[])
{
	test_object_factory();
	test_abstract_factory();

	return 0;
}