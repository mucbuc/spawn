
namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // abstract_factory<T, U> 
	/////////////////////////////////////////////////////////////////////////////////////////////
    template< template<class...> class U, class ... T >
    template< class V > 
    V * abstract_factory< U, T ... >::create()
    {
        U< V > & unit( * this ); 
        return unit.invoke_create( type_to_type<V>() ); 
    }   
} // om636

