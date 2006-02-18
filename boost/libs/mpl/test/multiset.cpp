
// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/multiset/multiset0.hpp>

#include <boost/mpl/insert.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/aux_/test.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/find.hpp>

MPL_TEST_CASE()
{
    typedef multiset0<> s0;
    typedef insert<s0,int>::type s1;
    typedef insert<s1,char&>::type s2;
    typedef insert<s2,int>::type s3;
    typedef insert<s3,abstract>::type s4;
    
    MPL_ASSERT_RELATION( (count<s0,int>::value), ==, 0 );
    MPL_ASSERT_RELATION( (count<s1,int>::value), ==, 1 );
    MPL_ASSERT_RELATION( (count<s2,int>::value), ==, 1 );
    MPL_ASSERT_RELATION( (count<s2,char&>::value), ==, 1 );
    MPL_ASSERT_RELATION( (count<s3,int>::value), ==, 2 );
    MPL_ASSERT_RELATION( (count<s3,char&>::value), ==, 1 );
    MPL_ASSERT_RELATION( (count<s4,abstract>::value), ==, 1 );
}


// Use a template for testing so that GCC will show us the actual types involved
template <class S>
void test()
{
    BOOST_MPL_ASSERT_RELATION( size<S>::value, ==, 3 );

    typedef typename end<S>::type not_found;
    BOOST_MPL_ASSERT_NOT(( is_same<BOOST_DEDUCED_TYPENAME find<S,int>::type,not_found> ));
    BOOST_MPL_ASSERT_NOT(( is_same<BOOST_DEDUCED_TYPENAME find<S,long>::type,not_found> ));
    BOOST_MPL_ASSERT_NOT(( is_same<BOOST_DEDUCED_TYPENAME find<S,char>::type,not_found> ));
    BOOST_MPL_ASSERT(( is_same<BOOST_DEDUCED_TYPENAME find<S,char*>::type,not_found> ));
};

MPL_TEST_CASE()
{
    typedef insert<multiset0<>, int> set_of_1_int;
    typedef begin<set_of_1_int>::type iter_to_1_int;
    BOOST_MPL_ASSERT(( is_same< deref<iter_to_1_int>::type, int > ));
    
    typedef multiset0<> s0;
    typedef insert<s0,int>::type s1;
    typedef insert<s1,long>::type s2;
    typedef insert<s2,char>::type myset;
    
    test<myset>();
    test<myset::type>();
}
