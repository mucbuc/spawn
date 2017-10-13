
#include "lib/spawn/src/abstract_factory.h"
#include "lib/spawn/src/concrete_factory.h"

struct Abstract1 {
    virtual const char* hello() = 0;
};

struct Abstract2 {
    virtual const char* hello() = 0;
};

struct Concrete1 : Abstract1 {
    const char* hello()
    {
        return "hello";
    }
};

struct Concrete2 : Abstract2 {
    const char* hello()
    {
        return 0;
    }
};

void test_abstract_factory()
{
    using namespace om636;
    using namespace std;

    typedef abstract_factory<abstract_unit, Abstract1, Abstract2> abstract_type;
    typedef concrete_factory<
        abstract_type,
        type_link<Concrete1, Abstract1>,
        type_link<Concrete2, Abstract2>>
        concrete_type;

    concrete_type factory;
    ASSERT(!strcmp(factory.create<Abstract1>()->hello(), "hello"));
    ASSERT(!factory.create<Abstract2>()->hello());

    cout << "test_abstract_factory passed" << endl;
}

void test_abstract_factory2()
{
    using namespace om636;
    using namespace std;

    typedef abstract_factory<abstract_unit> abstract_type;
    typedef concrete_factory<
        abstract_type>
        concrete_type;

    concrete_type factory;

    cout << "test_abstract_factory passed" << endl;
}