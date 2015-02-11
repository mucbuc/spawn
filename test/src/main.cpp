#include <iostream>
#include <functional>
#include <string>

#include "../plank/src/test.h"
#include "../../src/object_factory.h"

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

	ASSERT( ! strcmp(off.create( 3 ), "hello") );
}

int main(int argc, const char * argv[])
{
	run_test();
	return 0;
}