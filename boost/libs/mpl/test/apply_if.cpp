//-----------------------------------------------------------------------------
// boost mpl/test/apply_if.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/apply_if.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/identity.hpp"
#include "boost/mpl/assert_is_same.hpp"

namespace mpl = boost::mpl;

int main()
{
    typedef mpl::apply_if<
          mpl::true_
        , mpl::identity<char>
        , mpl::identity<long>
        >::type t1;

    typedef mpl::apply_if_c<
          true
        , mpl::identity<char>
        , mpl::identity<long>
        >::type t2;

    BOOST_MPL_ASSERT_IS_SAME(t1, char);
    BOOST_MPL_ASSERT_IS_SAME(t2, char);

    typedef mpl::apply_if<
          mpl::false_
        , mpl::identity<char>
        , mpl::identity<long>
         >::type t3;

    typedef mpl::apply_if_c<
          false
        , mpl::identity<char>
        , mpl::identity<long>
        >::type t4;

    BOOST_MPL_ASSERT_IS_SAME(t3, long);
    BOOST_MPL_ASSERT_IS_SAME(t4, long);

    return 0;
}
