//-----------------------------------------------------------------------------
// boost mpl/aux_/iter_push_front.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED

#include "boost/mpl/push_front.hpp"

namespace boost {
namespace mpl {
namespace aux {

template<
      typename Sequence
    , typename Iterator
    >
struct iter_push_front
{
    typedef typename push_front<
          Sequence
        , typename Iterator::type
        >::type type;
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITER_PUSH_FRONT_HPP_INCLUDED
