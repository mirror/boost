
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License,Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/single_view.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/test.hpp>

MPL_TEST_CASE()
{
    typedef single_view<int> view;
    typedef begin<view>::type first;
    typedef end<view>::type last;

    MPL_ASSERT(( is_same<first::type,int> ));
    MPL_ASSERT(( is_same<first::next,last> ));
    MPL_ASSERT(( is_same<last::prior,first> ));

    MPL_ASSERT_RELATION( size<view>::value, ==, 1 );
}
