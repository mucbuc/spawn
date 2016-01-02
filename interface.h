#ifndef INTERFACE_H__INCLUDE_GUARD__LJDFD88989898989
#define INTERFACE_H__INCLUDE_GUARD__LJDFD88989898989

#include <algorithm>
#include "typeutills.h"

namespace om636
{   
	struct null_type 
	{	typedef null_type value_type; 	};
	
	struct empty_type 
    {
        empty_type(...) {}
    };

    template< class > 
    struct empty_template
    {
        empty_template(...) {}
    };
    
	template<class>
	struct type_to_type {};

	template<int>
	struct int_to_type {};
    
    template<class T, class U> 
    void hetero_swap(T &, U &);    
    
    template<class T> 
    void hetero_swap(T &, T &);    
     
}	// om636

#include "interface.hxx"

#endif // INTERFACE_H__INCLUDE_GUARD__LJDFD88989898989
