//-----------------------------------------------------------------------------
// boost mpl/aux_/apply_1st.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
#define BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED

#include "boost/mpl/apply.hpp"

namespace boost {
namespace mpl {
namespace aux {

struct apply_1st
{
    template< typename Pair, typename T > struct apply
        : apply2<
              typename Pair::first
            , typename Pair::second
            , T
            >
    {
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_APPLY_1ST_HPP_INCLUDED
