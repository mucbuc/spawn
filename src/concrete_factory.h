#ifndef CONCRETE_FACTORY_H_54654LKJ546L4
	#define CONCRETE_FACTORY_H_54654LKJ546L4

#include <lib/spawn/src/createfwd.h>

namespace om636
{
    template<class T, class U, class V, class ... W> 
    struct concrete_factory<T, type_link<U, V>, W ... >
    : concrete_factory<T, W ... >
    {   
        virtual U * invoke_create(type_to_type<V>);
        virtual ~concrete_factory() = default;
    };

    template<class T, class U, class V> 
    struct concrete_factory<T, type_link<U, V> > 
    : T
    {
        virtual U * invoke_create(type_to_type<V>);
        virtual ~concrete_factory() = default;
    };

    template<class T>
    struct concrete_factory<T>
    {
        virtual ~concrete_factory() = default;
    };
    
} // om636
	
#include "concrete_factory.hxx"

#endif // CONCRETE_FACTORY_H_54654LKJ546L4