//-----------------------------------------------------------------------------
// boost mpl/test/logical.cpp source file
// See http://www.boost.org for updates,documentation,and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/logical.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct my;
struct true_ : mpl::true_ {};
struct false_ : mpl::false_ {};

int main()
{
    BOOST_STATIC_ASSERT((mpl::and_< true_,true_ >::value == true));
    BOOST_STATIC_ASSERT((mpl::and_< false_,true_ >::value == false));
    BOOST_STATIC_ASSERT((mpl::and_< true_,false_ >::value == false));
    BOOST_STATIC_ASSERT((mpl::and_< false_,false_ >::value == false));
    BOOST_STATIC_ASSERT((mpl::and_< false_,my >::value == false));
    BOOST_STATIC_ASSERT((mpl::and_< false_,my,my >::value == false));

    BOOST_STATIC_ASSERT((mpl::or_< true_,true_ >::value == true));
    BOOST_STATIC_ASSERT((mpl::or_< false_,true_ >::value == true));
    BOOST_STATIC_ASSERT((mpl::or_< true_,false_ >::value == true));
    BOOST_STATIC_ASSERT((mpl::or_< false_,false_ >::value == false));
    BOOST_STATIC_ASSERT((mpl::or_< true_,my >::value == true));
    BOOST_STATIC_ASSERT((mpl::or_< true_,my,my >::value == true));

    BOOST_STATIC_ASSERT((mpl::not_< true_ >::value == false));
    BOOST_STATIC_ASSERT((mpl::not_< false_ >::value == true));
  
    return 0;
}
