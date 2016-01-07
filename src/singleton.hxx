namespace om636
{
	template<class T, class U, class V>
	typename singleton<T, U, V>::instance_type singleton<T, U, V>::m_instance( 0 );

	template<class T, class U, class V>
	bool singleton<T, U, V>::m_destroyed( false );

	/////////////////////////////////////////////////////////////////////////////////////////////
    // default_lifetime<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void default_lifetime<T>::dead_reference()
	{	ASSERT( false );	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void default_lifetime<T>::schedule_call( void(*p)() )
	{	atexit( p );	}

	/////////////////////////////////////////////////////////////////////////////////////////////
    // create_new<T>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	T * create_new<T>::	create()
	{	return new T;	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	template<class U>
	T * create_new<T>::	create(const U & i)
	{	return new T(i);	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T>
	void create_new<T>::destroy(T* _d)
	{	delete _d;	}

	/////////////////////////////////////////////////////////////////////////////////////////////
    // singleton<T, U, V>
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class V>
	typename singleton<T, U, V>::reference_type 
	singleton<T, U, V>::instance()
	{
		if (!m_instance)
		{
			if (m_destroyed)
			{
				lifetime_policy::dead_reference();
				m_destroyed = false;
			}
			
			m_instance = creation_policy::create();
			lifetime_policy::schedule_call( & destroy_singleton );
		}
		
		return * m_instance;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class V>
	template<class W>
	typename singleton<T, U, V>::reference_type 
	singleton<T, U, V>::instance(const W & i)
	{
		if (!m_instance)
		{
			if (m_destroyed)
			{
				lifetime_policy::dead_reference();
				m_destroyed = false;
			}
			
			m_instance = creation_policy::create(i);
			lifetime_policy::schedule_call( & destroy_singleton );
		}
		
		return * m_instance;
	}

    /////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class V>
	void singleton<T, U, V>::release()
    {
		ASSERT( !m_destroyed );
		
		creation_policy::destroy( m_instance );
		m_instance = 0;
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class V>
	singleton<T, U, V>::~singleton()
	{
		release(); 
        m_destroyed = true;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<class T, class U, class V>
	void singleton<T, U, V>::destroy_singleton()
	{	creation_policy::destroy( m_instance );	}

} // om636
