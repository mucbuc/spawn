#include <functional>
#include <iostream>
#include <string>

#include "src/abstract.h"
#include "src/object.h"
#include <tmp/src/test.h>

int main(int argc, const char* argv[])
{
    test_object_factory();
    test_abstract_factory();
    test_abstract_factory2();

    return 0;
}