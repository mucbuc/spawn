#ifndef _concrete_factory_H_eewgqwgjh
	#define _concrete_factory_H_eewgqwgjh

#include "typetree.h"
#include "createfwd.h"

namespace om636
{
    template<class T, template<class, class> class U, class ... V, class ... W> 
    struct concrete_factory
    : public
    {

    };


    template<class T, class U, class ... V>
    struct concrete_unit<T, U, V ... >
    : concrete_unit<T, U>
    : concrete_unit<T, V ... >
    {

    };

    template<template<class> class T, class U> 
    struct concrete_unit<T, U> 
    : public T<U> 
    {
        typedef T<U> base_type; 
        
        virtual concrete_type * do_create( om636::type_to_type<U> ) 
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