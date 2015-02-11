#ifndef _concrete_factory_H_eewgqwgjh
	#define _concrete_factory_H_eewgqwgjh

#include "typetree.h"
#include "createfwd.h"

namespace om636
{
    template<class T, class U> 
    struct concrete_unit : public U
    {
        typedef U base_type;
        typedef T concrete_type; 
        
        typedef typename base_type::product_list base_product_list;
        typedef typename base_product_list::right_type product_list; 
        typedef typename base_product_list::left_type abstract_type; 
        
        virtual concrete_type * do_create( om636::type_to_type<abstract_type> ) 
        {
            return new T(); 
        }
        
        virtual ~concrete_unit()
        {}
    };
    
    template<class T, template<class, class> class U, class V>
    class concrete_factory
        : public generate_linear_hierarchy< T, U, V >
    {
    public:
        typedef T concrete_product_list; 
        typedef V factory_type; 
    };
    
} // om636
	
#include "concrete_factory.hxx"

#endif // _concrete_factory_H_eewgqwgjh