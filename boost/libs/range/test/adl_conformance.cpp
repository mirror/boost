// Boost.Range library
//
//  Copyright Thorsten Ottosen 2003-2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#include <boost/detail/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#  pragma warn -8091 // supress warning in Boost.Test
#  pragma warn -8057 // unused argument argc/argv in Boost.Test
#endif

namespace boost
{
    namespace range_detail
    {
        template< class Range >
        inline typename Range::iterator begin( Range& r )
        {
           return r.begin();  
        }
    }
    
    template< class Range >
    inline typename Range::iterator begin( Range& r )
    {
        using range_detail::begin; // create ADL hook
        return begin( r );
    }
}


namespace find_templated
{
    template< class T >
    struct range
    {
        typedef int* iterator;

        range()                { /* allow const objects */ }
        iterator begin()       { return 0; }
        iterator begin() const { return 0; }
        iterator end()         { return 0; }
        iterator end() const   { return 0; }
    };
        
    //
    // A fully generic version here will create
    // ambiguity.
    //
    template< class T >
    inline typename range<T>::iterator begin( range<T>& r )
    {
        return r.begin();
    }
}

namespace find_non_templated
{
    struct range
    {
        typedef int* iterator;
        
        range()                { /* allow const objects */ }
        iterator begin()       { return 0; }
        iterator begin() const { return 0; }
        iterator end()         { return 0; }
        iterator end() const   { return 0; }
    };
    
    inline range::iterator begin( range& r )
    {
        return r.begin();
    }
}

struct range
{
    typedef int* iterator;

    range()                { /* allow const objects */ }
    iterator begin()       { return 0; }
    iterator begin() const { return 0; }
    iterator end()         { return 0; }
    iterator end() const   { return 0; }
};

inline range::iterator begin( range& r )
{
    return r.begin();
}   

void check_adl_conformance()
{
    find_templated::range<int>       r;
    const find_templated::range<int> r2;
    find_non_templated::range        r3;
    const find_non_templated::range  r4;
    range                            r5;
    const range                      r6;
    
    //
    // Notice how ADL kicks in even when we have qualified 
    // notation!
    //
    
    boost::begin( r );
    boost::begin( r2 );
    boost::begin( r3 );
    boost::begin( r4 );
    boost::begin( r5 );
    boost::begin( r6 );
}

#include <iostream>

int main()
{
    try
    {
        check_adl_conformance();
    }
    catch( ... )
    {
        std::cout << "error in test" << std::endl;
        return -1;
    }
    
    return 0;   
}

/*
#include <boost/test/included/unit_test_framework.hpp> 

using boost::unit_test_framework::test_suite;

test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite* test = BOOST_TEST_SUITE( "Range Test Suite" );

    test->add( BOOST_TEST_CASE( &check_adl_conformance ) );

    return test;
}
*/

