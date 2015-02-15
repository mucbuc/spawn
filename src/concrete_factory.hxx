namespace om636
{
    template<class T, class U, class V, class ... W> 
    U * concrete_factory<T, std::tuple<U, V>, W ... >::invoke_create(type_to_type<V>)
    {   
      	return new U;
    }

    template<class T, class U, class V> 
	U * concrete_factory<T, std::tuple<U, V> >::invoke_create(type_to_type<V>)
    {
        return new U;
    }
} // om636

