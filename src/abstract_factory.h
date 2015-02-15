#ifndef ABSTRACT_FACTOR_H_56353YHTDHDF
	#define ABSTRACT_FACTOR_H_56353YHTDHDF

namespace om636
{
    template<class T> 
    struct type_to_type
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
    class abstract_factory
        : public U< T ... >
    {
    public:
       
        template<class V> 
        V * create();
    };
    
} // om636
	
#include "abstract_factory.hxx"

#endif // ABSTRACT_FACTOR_H_56353YHTDHDF