#ifndef ABSTRACT_FACTOR_H_56353YHTDHDF
	#define ABSTRACT_FACTOR_H_56353YHTDHDF

#include <lib/spawn/src/createfwd.h>
#include <lib/static/interface.h>

namespace om636
{
    template<class T, class U>
    struct type_link
    {};
    
    template<class T, class ... U>
    struct abstract_unit<T, U ...>
    : abstract_unit<T>
    , abstract_unit<U ...>
    {
        virtual ~abstract_unit() = default;
    };

    template<class T> 
    struct abstract_unit<T>
    {
        virtual T * invoke_create( type_to_type<T> ) = 0;
        virtual ~abstract_unit() = default;
    };

    template< template<class...> class U, class ... T >
    struct abstract_factory
    : U< T ... >
    {
        template<class V> 
        V * create();
    };

    template< template<class...> class U >
    struct abstract_factory<U>
    {};
    
} // om636
	
#include "abstract_factory.hxx"

#endif // ABSTRACT_FACTOR_H_56353YHTDHDF