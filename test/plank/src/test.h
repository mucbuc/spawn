#ifndef TEST_H
#define TEST_H

#include <iostream>

static const char * code_red( "\x1b[31m" ); 
static const char * code_reset( "\x1b[39;49m" );	

#define ASSERT( p ) \
if (!(p)) { \
	using namespace std; \
	cout << code_red; \
	cout << "* assert failed *\n"; \
	cout << __FILE__ << ":"; \
	cout << __LINE__ << ":\n"; \
	cout << "  " << __PRETTY_FUNCTION__; \
	cout << code_reset << endl; \
	exit(1); \
}

#endif // TEST_H