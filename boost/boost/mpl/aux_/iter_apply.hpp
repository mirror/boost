//-----------------------------------------------------------------------------
// boost mpl/aux_/iter_apply.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ITER_APPLY_HPP_INCLUDED
#define BOOST_MPL_ITER_APPLY_HPP_INCLUDED

#include "boost/mpl/apply.hpp"

namespace boost {
namespace mpl {
namespace aux {

template<
      typename F
    , typename Iterator
    >
struct iter_apply1
    : apply1<F,typename Iterator::type>
{
};

template<
      typename F
    , typename Iterator1
    , typename Iterator2
    >
struct iter_apply2
    : apply2<
          F
        , typename Iterator1::type
        , typename Iterator2::type
        >
{
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITER_APPLY_HPP_INCLUDED
