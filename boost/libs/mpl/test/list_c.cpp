
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/list_c.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/static_assert.hpp>

#include <boost/mpl/aux_/test.hpp>


#if !BOOST_WORKAROUND(BOOST_MSVC,<= 1200)
MPL_TEST_CASE()
{
    typedef list_c<bool,true>::type list1;
    typedef list_c<bool,false>::type list2;

    MPL_ASSERT_RELATION(  front<list1>::type::value, ==, true );
    MPL_ASSERT_RELATION(  front<list2>::type::value, ==, false );
}
#endif

MPL_TEST_CASE()
{
    typedef list_c<int,-1>::type list1;
    typedef list_c<int,0,1>::type list2;
    typedef list_c<int,1,2,3>::type list3;

    MPL_ASSERT_RELATION( size<list1>::value, ==, 1 );
    MPL_ASSERT_RELATION( size<list2>::value, ==, 2 );
    MPL_ASSERT_RELATION( size<list3>::value, ==, 3 );
    MPL_ASSERT_RELATION( front<list1>::type::value, ==, -1 );
    MPL_ASSERT_RELATION( front<list2>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( front<list3>::type::value, ==, 1 );
}

MPL_TEST_CASE()
{
    typedef list_c<unsigned,0>::type list1;
    typedef list_c<unsigned,1,2>::type list2;

    MPL_ASSERT_RELATION( size<list1>::value, ==, 1 );
    MPL_ASSERT_RELATION( size<list2>::value, ==, 2 );
    MPL_ASSERT_RELATION( front<list1>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( front<list2>::type::value, ==, 1 );
}

MPL_TEST_CASE()
{
    typedef list_c<unsigned,2,1> l2;
    
    typedef begin<l2>::type i1;
    typedef next<i1>::type  i2;
    typedef next<i2>::type  i3;
    
    MPL_ASSERT_RELATION( deref<i1>::type::value, ==, 2 );
    MPL_ASSERT_RELATION( deref<i2>::type::value, ==, 1 );
    MPL_ASSERT(( is_same< i3, end<l2>::type > ));
}
