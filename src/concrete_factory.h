#ifndef _concrete_factory_H_eewgqwgjh
	#define _concrete_factory_H_eewgqwgjh

#include <tuple>

#include "createfwd.h"

namespace om636
{
    template<class T, class U, class V, class ... W> 
    struct concrete_factory<T, std::tuple<U, V>, W ... >
    : concrete_factory<T, W ... >
    {   
        virtual U * invoke_create(type_to_type<V>);
        virtual ~concrete_factory() = default;
    };

    template<class T, class U, class V> 
    struct concrete_factory<T, std::tuple<U, V> > 
    : T
    {
        virtual U * invoke_create(type_to_type<V>);
        virtual ~concrete_factory() = default;
    };
    
} // om636
	
#include "concrete_factory.hxx"

#endif // _concrete_factory_H_eewgqwgjh