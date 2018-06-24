/* 
    Reference: http://www.drdobbs.com/article/print?articleId=184403745
*/

#ifndef ASSERT_H_9879879hkjh
#define ASSERT_H_9879879hkjh

#include <assert.h>
#include <cstring>
#include <iostream>

#ifdef NDEBUG

     #define ASSERT( expr ) \
        if (false); \
        else    \
            struct local_t  \
            {   \
                local_t( const asserter_t & ) {} \
            } local_obj = asserter_t(false)

        // asserter_t
        class asserter_t
        {
        public:
            template<class T> const asserter_t operator()(const T &) const { return asserter_t(); } 
        };

#else

    #define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
    #define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
    #define SMART_ASSERT_OP(x, next) SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next

    #ifndef TARGET_TEST
        #define TARGET_TEST 0 
    #endif

    #define ASSERT( expr ) \
        if (!TARGET_TEST && (expr)); \
        else    \
            struct local_t  \
            {   \
                local_t( const asserter_t & o ) \
                {   \
                    if( !(o.pass()) )   \
                        assert(false);  \
                }   \
            } \
            local_obj = \
            asserter_t( expr ) \
            .print_message( __FILE__, __LINE__, __FUNCTION__, #expr ) \
            .archive_result( __FILE__, __LINE__, __FUNCTION__, #expr ) \
            .SMART_ASSERT_A

    // asserter_t
    struct asserter_t final
    {	
        asserter_t(bool); 

        bool pass() const;
        
        const asserter_t & print_message(
            const char * file, 
            int line, 
            const char * function, 
            const char * = "" ) const;  

        const asserter_t & archive_result(
            const char * file, 
            int line, 
            const char * function, 
            const char * = "" ) const; 
        
        template<class U> const asserter_t & print_current_val(const U &, const char*) const; 
       
        asserter_t & SMART_ASSERT_A; 
        asserter_t & SMART_ASSERT_B; 
                
    private:
        const bool m_value;
    };

    #include "asserter.hxx"

#endif // NDEBUG

#endif // ASSERT_H_9879879hkjh