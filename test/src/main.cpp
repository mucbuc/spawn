#include <iostream>
#include <functional>
#include <string>
#include <tuple>

#include "../plank/src/test.h"
#include "../../src/object_factory.h"
#include "../../src/abstract_factory.h"
#include "../../src/concrete_factory.h"

struct Abstract1
{
 	virtual const char * hello() = 0;
};

struct Abstract2
{
 	virtual const char * hello() = 0;
};

struct Concrete1 : Abstract1
{	
	const char * hello()
	{
		return "hello";
	}
};

struct Concrete2 : Abstract2
{
	const char * hello()
	{
		return 0;
	}
};

void run_abstract_factory_test()
{
	using namespace om636;
	typedef abstract_factory< om636::abstract_unit, Abstract1, Abstract2 > abstract_type;
	typedef concrete_factory< 
		abstract_type, 
		std::tuple< Concrete1, Abstract1>,
		std::tuple< Concrete2, Abstract2> > 
	concrete_type;
	
	concrete_type factory; 
	ASSERT( !factory.create<Abstract2>()->hello() );
	ASSERT( !strcmp(factory.create<Abstract1>()->hello(), "hello") );
}

void run_object_factory_test() 
{
	using namespace std;
	typedef function< const char * () > functor_type;
	
	om636::object_factory< int, functor_type > off;
	off.register_create( 3, [](){
		return "hello";
	});

	ASSERT( !strcmp(off.create( 3 ), "hello") );
}


int main(int argc, const char * argv[])
{

	run_object_factory_test();
	run_abstract_factory_test();

	return 0;
}