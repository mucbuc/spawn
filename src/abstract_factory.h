#ifndef _abstract_factory_H_kjh32lkjh
	#define _abstract_factory_H_kjh32lkjh

#include "typetree.h"

namespace om636
{
    
    template<class T> 
    struct abstract_unit
    {
        virtual T * do_create( om636::type_to_type<T> ) = 0;
        virtual ~abstract_unit() {}
    };

    template< class T, template<class> class U >
    class abstract_factory
        : public generate_scatter_hierarchy< T, U >
    {
    public:
        typedef T product_list; 
        
        template<class V> 
        V * create(); 
    };
    
} // om636
	
#include "abstract_factory.hxx"

#endif // _abstract_factory_H_kjh32lkjh