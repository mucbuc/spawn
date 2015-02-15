
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

void test_abstract_factory()
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

	std::cout << "test_abstract_factory passed" << std::endl;
}