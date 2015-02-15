
#include "../../src/object_factory.h"

void test_object_factory() 
{
	using namespace std;
	typedef function< const char * () > functor_type;
	
	om636::object_factory< int, functor_type > off;
	off.register_create( 3, [](){
		return "hello";
	});

	ASSERT( !strcmp(off.create( 3 ), "hello") );

	std::cout << "test_object_factory passed" << std::endl;
}