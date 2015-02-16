#ifndef CREATEFWD_H__INCLUDE_GUARD__ERERE53553
	#define CREATEFWD_H__INCLUDE_GUARD__ERERE53553

namespace om636
{
	// abstract_factory.h
	template<class> struct type_to_type;
	template<class, class> struct type_link;
    template<class...> struct abstract_unit;
    template< template<class...> class, class ... > struct abstract_factory;
	
    // concrete_factory.h
    template<class, class ... > struct concrete_factory;

	// object_factory.h
	template<class, class, class = int> class object_factory;
		
	// singleton
	template<class> struct default_lifetime;
	template<class> struct create_new;
	template<class, class, class> class singleton;

} // om636

#endif // __CREATEFWD_H__INCLUDE_GUARD__ERERE53553