/*
	objective:
		object/clone factory 
		
	notes:
		could maybe be concrete case of some function map/vector 
		class used for object factories and multimethods??????
	
	example:
	{
		typedef functor< dynamic_policy< char*(*)() > > functor_type;
		functor_type create( &fuck_you );		
		object_factory< int, functor_type > of;
		of.register_create( 3, create );
		cout << string( of.create( 3 ) ) << std::endl; 
	}

 
    log: 
        4.3.12: removed create with parameter. goes a bit against the factory mothod design pattern. create the object 
                and then call "read". 
*/

#ifndef OBJECT_FACTORY_H_34LKJ532445345
	#define OBJECT_FACTORY_H_34LKJ532445345

#include <map>
#include "createfwd.h"

namespace om636
{
	using namespace std;

	template<class T, class F, class E>
	class object_factory
	{ 
	public:	
		typedef T key_type;
		typedef F functor_type;
		typedef E error_policy;

		typedef typename functor_type::result_type result_type;
        typedef map< key_type, functor_type > map_type;
		typedef typename map_type::iterator iterator_type;
		typedef typename map_type::const_iterator const_iterator;
				
		object_factory();
		bool register_create( const key_type &, const functor_type&);		
		bool unregister_create( const key_type & );
		
		virtual result_type create( const key_type & ) const;
		
	private:	
		map_type _creator;
		
		// blocked 
		object_factory( const object_factory& );
		object_factory & operator=(const object_factory&);
	};
	
} // om636
	
#include "object_factory.hxx"

#endif // OBJECT_FACTORY_H_34LKJ532445345