
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/joint_view.hpp>

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef joint_view<
          range_c<int,0,10>
        , range_c<int,10,15>
        > numbers;

    typedef range_c<int,0,15> answer;

    MPL_ASSERT(( equal<numbers,answer> ));
    MPL_ASSERT_RELATION( size<numbers>::value, ==, 15 );
}
