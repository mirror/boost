
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef range_c<int,0,0> range0;
    typedef range_c<int,0,1> range1;
    typedef range_c<int,0,10> range10;

    MPL_ASSERT_RELATION( size<range0>::value, ==, 0 );
    MPL_ASSERT_RELATION( size<range1>::value, ==, 1 );
    MPL_ASSERT_RELATION( size<range10>::value, ==, 10 );

    MPL_ASSERT(( empty<range0> ));
    MPL_ASSERT_NOT(( empty<range1> ));
    MPL_ASSERT_NOT(( empty<range10> ));

    MPL_ASSERT(( is_same<begin<range0>::type, end<range0>::type > ));
    MPL_ASSERT_NOT(( is_same<begin<range1>::type, end<range1>::type > ));
    MPL_ASSERT_NOT(( is_same<begin<range10>::type, end<range10>::type > ));

    MPL_ASSERT_RELATION( front<range1>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( back<range1>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( front<range10>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( back<range10>::type::value, ==, 9 );
}

MPL_TEST_CASE()
{
    typedef range_c<int,0,10> range10;
    typedef begin<range10>::type i0;
    typedef next<i0>::type i1;
    typedef next<i1>::type i2;
    typedef next<i2>::type i3;
    typedef next<i3>::type i4;
    typedef next<i4>::type i5;
    typedef next<i5>::type i6;
    typedef next<i6>::type i7;
    typedef next<i7>::type i8;
    typedef next<i8>::type i9;
    typedef next<i9>::type i10;

    MPL_ASSERT_RELATION( deref<i0>::type::value, ==, 0 );
    MPL_ASSERT_RELATION( deref<i1>::type::value, ==, 1 );
    MPL_ASSERT_RELATION( deref<i2>::type::value, ==, 2 );
    MPL_ASSERT_RELATION( deref<i3>::type::value, ==, 3 );
    MPL_ASSERT_RELATION( deref<i4>::type::value, ==, 4 );
    MPL_ASSERT_RELATION( deref<i5>::type::value, ==, 5 );
    MPL_ASSERT_RELATION( deref<i6>::type::value, ==, 6 );
    MPL_ASSERT_RELATION( deref<i7>::type::value, ==, 7 );
    MPL_ASSERT_RELATION( deref<i8>::type::value, ==, 8 );
    MPL_ASSERT_RELATION( deref<i9>::type::value, ==, 9 );
}
