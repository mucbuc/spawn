
namespace om636 {
/////////////////////////////////////////////////////////////////////////////////////////////
// object_factory
/////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class F, class E>
object_factory<T, F, E>::object_factory() {}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class F, class E>
bool object_factory<T, F, E>::register_create(const key_type& id, const functor_type& create)
{
    return _creator.insert(make_pair(id, create)).second;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class F, class E>
bool object_factory<T, F, E>::unregister_create(const key_type& id)
{
    return _creator.erase(id) == 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class F, class E>
auto object_factory<T, F, E>::create(const key_type& id) const -> result_type
{
    const_iterator i(_creator.find(id));
    if (i != _creator.end())
        return (i->second)();

    //error_policy();
    return result_type();
}

} // om636
