//-----------------------------------------------------------------------------
// boost mpl/test/bind.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/bind.hpp"
#include "boost/mpl/apply.hpp"
#include "boost/mpl/assert_is_same.hpp"
#include "boost/type_traits/is_same.hpp"

namespace mpl = boost::mpl;

namespace {

struct f1
{
    template< typename T1 > struct apply
    {
        typedef T1 type;
    };
};

struct f5
{
    template< typename T1, typename T2, typename T3, typename T4, typename T5 >
    struct apply
    {
        typedef T5 type;
    };
};

} // namespace

int main()
{
    using namespace mpl::placeholders;
    
    typedef mpl::apply1< mpl::bind1<f1,_1>,int >::type r11;
    typedef mpl::apply5< mpl::bind1<f1,_5>,void,void,void,void,int >::type r12;
    BOOST_MPL_ASSERT_IS_SAME(r11,int);
    BOOST_MPL_ASSERT_IS_SAME(r12,int);
    
    typedef mpl::apply5< mpl::bind5<f5,_1,_2,_3,_4,_5>,void,void,void,void,int >::type r51;
    typedef mpl::apply5< mpl::bind5<f5,_5,_4,_3,_2,_1>,int,void,void,void,void >::type r52;
    BOOST_MPL_ASSERT_IS_SAME(r51,int);
    BOOST_MPL_ASSERT_IS_SAME(r52,int);
    
    return 0;
}
