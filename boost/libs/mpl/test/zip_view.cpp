//-----------------------------------------------------------------------------
// boost mpl/test/zip_view.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/zip_view.hpp"
#include "boost/mpl/transform_view.hpp"
#include "boost/mpl/filter_view.hpp"
#include "boost/mpl/range_c.hpp"
#include "boost/mpl/list.hpp"
#include "boost/mpl/at.hpp"
#include "boost/mpl/equal.hpp"
#include "boost/mpl/equal_to.hpp"
#include "boost/mpl/math/is_even.hpp"
#include "boost/static_assert.hpp"

using namespace boost::mpl;

template< typename BinaryOp >
struct apply_two_args_seq
{
    template< typename Args > struct apply
    {
        typedef typename apply2<
              BinaryOp
            , typename at_c<Args,0>::type
            , typename at_c<Args,1>::type
            >::type type;
    };
};

int main()
{
    typedef range_c<int,0,10> s1;
    typedef range_c<int,10,20> s2;

    typedef transform_view<
          zip_view< list<s1,s2> >
        , apply_two_args_seq< plus<> >
        > result;

    BOOST_STATIC_ASSERT((equal< 
          result
        , filter_view< range_c<int,10,30>, math::is_even<_> >
        , equal_to<_,_>
        >::type::value));

    return 0;
}
