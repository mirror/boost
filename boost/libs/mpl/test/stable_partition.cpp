//-----------------------------------------------------------------------------
// libs mpl/test/stable_partition.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/stable_partition.hpp"

#include "boost/static_assert.hpp"
#include "boost/mpl/list_c.hpp"
#include "boost/mpl/equal.hpp"

#include "boost/mpl/less.hpp"
#include "boost/mpl/placeholders.hpp"
#include "boost/mpl/int.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::list_c<int, 3, 4, 0, -5, 8, -1, 7>::type numbers;
    typedef mpl::list_c<int, 0, -5, -1>::type manual_first;
    typedef mpl::list_c<int, 3, 4, 8, 7>::type manual_second;

    //////

    typedef mpl::stable_partition<
          numbers
        , mpl::less< mpl::_, mpl::int_<3> >
        >::type result1;

    typedef result1::first first1;
    BOOST_STATIC_ASSERT((mpl::equal< first1,manual_first >::type::value));
    typedef result1::second second1;
    BOOST_STATIC_ASSERT((mpl::equal< second1,manual_second >::type::value));

    //////

    typedef mpl::stable_partition<
          numbers
        , mpl::lt< 3 >
        >::type result2;

    typedef result2::first first2;
    BOOST_STATIC_ASSERT((mpl::equal< first2,manual_first >::type::value));
    typedef result2::second second2;
    BOOST_STATIC_ASSERT((mpl::equal< second2,manual_second >::type::value));

    return 0;
}
