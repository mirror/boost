
// + file: libs/mpl/test/set.cpp
// + last modified: 02/may/03

// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/set/set0.hpp"
#include "boost/mpl/has_key.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

#define MPL_TEST_CASE( test_name ) void test_name()
#define MPL_TEST_ASSERT( expr ) BOOST_STATIC_ASSERT( expr )

struct UDT {};
struct incomplete;

MPL_TEST_CASE( empty_set )
{
    typedef mpl::set0<> s;
    
    MPL_TEST_ASSERT(( !mpl::has_key<s,char>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,int>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,UDT>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,incomplete>::type::value ));

    MPL_TEST_ASSERT(( !mpl::has_key<s,char const>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,int const>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,UDT const>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,incomplete const>::type::value ));

    MPL_TEST_ASSERT(( !mpl::has_key<s,int*>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,UDT*>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,incomplete*>::type::value ));

    MPL_TEST_ASSERT(( !mpl::has_key<s,int&>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,UDT&>::type::value ));
    MPL_TEST_ASSERT(( !mpl::has_key<s,incomplete&>::type::value ));

}


int main()
{
    
    return 0;
}
