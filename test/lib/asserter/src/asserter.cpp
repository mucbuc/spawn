#include <assert.h>

#include "archiver.h"
#include "asserter.h"

#undef SMART_ASSERT_A 
#undef SMART_ASSERT_B
#undef SMART_ASSERT_OP
#undef SMART_ASSERT

#ifndef NDEBUG

/////////////////////////////////////////////////////////////////////////////////////////////
// asserter_t
/////////////////////////////////////////////////////////////////////////////////////////////
asserter_t::asserter_t(bool value) 
	: SMART_ASSERT_A( * this )
    , SMART_ASSERT_B( * this )
    , m_value( value )
{}

/////////////////////////////////////////////////////////////////////////////////////////////
bool asserter_t::pass() const
{	
    return m_value; 	
}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_t & asserter_t::print_message(
    const char * file, 
    int line, 
    const char * function, 
    const char * message) const
{
    static const char * code_red( "\x1b[31m" ); 
    static const char * code_reset( "\x1b[39;49m" );    

    using namespace std;

    if (pass()) 
    {
        cout << "assertion passed: " << message << endl 
             << "file: " << file << endl 
             << "line: " << line << endl 
             << "function: " << function << endl;
    }
    else 
    {
        cout << code_red
             << "assertion failed: " << message << endl 
             << "file: " << file << endl 
             << "line: " << line << endl 
             << "function: " << function
             << code_reset << endl;
    }
    return * this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_t & asserter_t::archive_result(
    const char * file, 
    int line, 
    const char * function, 
    const char * message ) const
{
    auto & a( private_assert::archiver::instance() );
    if (pass())
        a.pass();
    else 
        a.fail( file, line, function, message );
    return * this;
}

#endif // NDEBUG




