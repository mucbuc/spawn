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
        virtual ~abstract_unit() {}
    };

    template<class T> 
    struct abstract_unit<T>
    {
        virtual T * do_create( type_to_type<T> ) = 0;
        virtual ~abstract_unit() {}
    };

    template< template<class...> class U, class ... T >
    class abstract_factory
        : public U< T ... >
    {
    public:
       
        template<class V> 
        V * create();

        template< template<class, class ..., class ...> class V, class ... W >
        struct concrete_factory
        {
            typedef V< abstract_factory, T ..., W ... > result_type;
        };
    };
    
} // om636
	
#include "abstract_factory.hxx"

#endif // ABSTRACT_FACTOR_H_56353YHTDHDF