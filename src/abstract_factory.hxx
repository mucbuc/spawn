
namespace om636
{
	/////////////////////////////////////////////////////////////////////////////////////////////
    // abstract_factory<T, U> 
	/////////////////////////////////////////////////////////////////////////////////////////////
    template< class T, template<class> class U >
    template< class V > 
    V * abstract_factory< T, U >::create()
    {
        U< V > & unit( * this ); 
        return unit.do_create( type_to_type<V>() ); 
    }   
} // om636

