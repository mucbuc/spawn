#include <functional>
#include <iostream>
#include <string>

#include <tmp/src/test.h>
#include "src/abstract.h"
#include "src/object.h"

int main(int argc, const char* argv[])
{
    test_object_factory();
    test_abstract_factory();
    test_abstract_factory2();

    return 0;
}