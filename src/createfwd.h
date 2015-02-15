#ifndef CREATEFWD_H__INCLUDE_GUARD__ERERE53553
	#define CREATEFWD_H__INCLUDE_GUARD__ERERE53553

namespace om636
{
	// abstract_factory.h
    template<class...> struct abstract_unit;
    template< template<class...> class = abstract_unit, class ... > class abstract_factory;
	
    // concrete_factory.h
    //template<class, class, class ...> struct concrete_unit;
    template<class, class ... > struct concrete_factory;

	// object_factory.h
	template<class, class, class = int> class object_factory;
		
	// singleton
	template<class> struct default_lifetime;
	template<class> struct create_new;
	template<class, class, class> class singleton;

} // om636

#endif // __CREATEFWD_H__INCLUDE_GUARD__ERERE53553