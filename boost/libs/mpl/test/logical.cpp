//-----------------------------------------------------------------------------
// boost mpl/test/logical.cpp source file
// See http://www.boost.org for updates,documentation,and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use,copy,modify,distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#include "boost/mpl/logical.hpp"
#include "boost/mpl/bool_c.hpp"
#include "boost/static_assert.hpp"

namespace mpl = boost::mpl;

struct my;
struct true_c : mpl::true_c {};
struct false_c : mpl::false_c {};

int main()
{
    BOOST_STATIC_ASSERT((mpl::logical_and< true_c,true_c >::value == true));
    BOOST_STATIC_ASSERT((mpl::logical_and< false_c,true_c >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_and< true_c,false_c >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_and< false_c,false_c >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_and< false_c,my >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_and< false_c,my,my >::value == false));

    BOOST_STATIC_ASSERT((mpl::logical_or< true_c,true_c >::value == true));
    BOOST_STATIC_ASSERT((mpl::logical_or< false_c,true_c >::value == true));
    BOOST_STATIC_ASSERT((mpl::logical_or< true_c,false_c >::value == true));
    BOOST_STATIC_ASSERT((mpl::logical_or< false_c,false_c >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_or< true_c,my >::value == true));
    BOOST_STATIC_ASSERT((mpl::logical_or< true_c,my,my >::value == true));

    BOOST_STATIC_ASSERT((mpl::logical_not< true_c >::value == false));
    BOOST_STATIC_ASSERT((mpl::logical_not< false_c >::value == true));
  
    return 0;
}
