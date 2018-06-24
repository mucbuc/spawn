/*
	objective:
		- enforce only instance
		- global access
	
	customization points:
		- held type
		- life time policy 
		- creation policy
		
	blocked:
		default constructor
		copy constructor
		assignment
		destructor
*/

#ifndef SINGLETON_H_8900700
#define SINGLETON_H_8900700

#include <cstdlib>

namespace om636 {
template <class T>
struct default_lifetime {
    static void dead_reference();
    static void schedule_call(void (*p)());
};

template <class T>
struct create_new {
    static T* create();
    template <class U>
    static T* create(const U&);
    static void destroy(T*);
};

template <class T, class U, class V>
class singleton {
    // undefined
    singleton(const singleton&);
    singleton& operator=(const singleton&);

public:
    // types
    typedef T* instance_type;
    typedef T& reference_type;
    typedef T value_type;
    typedef U lifetime_policy;
    typedef V creation_policy;

    // access
    static reference_type instance();
    template <class W>
    static reference_type instance(const W&);

    static void release();

private:
    // resources
    singleton();
    ~singleton();
    static void destroy_singleton();

    // members
    static instance_type m_instance;
    static bool m_destroyed;
};
} // om636

#include "singleton.hxx"

#endif // SINGLETON_H_8900700