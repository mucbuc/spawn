#include <iostream>
#include <functional>
#include <string>

#include "../plank/src/test.h"
#include "../../src/object_factory.h"
#include "../../src/abstract_factory.h"

const char * fuck_you()
{
	static std::string local( "hello" ); 
	return local.c_str();
}

void run_test() 
{
	using namespace std;
	typedef function< const char * () > functor_type;
	
	functor_type create( & fuck_you );		
	om636::object_factory< int, functor_type > off;
	off.register_create( 3, create );

	ASSERT( !strcmp(off.create( 3 ), "hello") );
}

struct Abstract1
{
	
};

struct Abstract2
{
};

struct Factory
: public om636::abstract_factory< om636::abstract_unit, Abstract1, Abstract2 >
{
	Abstract1 * do_create( om636::type_to_type<Abstract1> )
	{
		return new Abstract1;
	}

	Abstract2 * do_create( om636::type_to_type<Abstract2> )
	{
		return new Abstract2;
	}
};

int main(int argc, const char * argv[])
{
	using namespace om636;

	run_test();

	Factory factory;

	factory.create<Abstract1>();

	return 0;
}