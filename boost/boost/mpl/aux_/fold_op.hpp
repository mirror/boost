//-----------------------------------------------------------------------------
// boost mpl/aux_/fold_op.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED

#include "boost/mpl/apply.hpp"

namespace boost {
namespace mpl {
namespace aux {

// hand-written version is more efficient than bind/lambda expression
template< typename Op >
struct fold_op
{
    template< typename T1, typename T2 > struct apply
    {
        typedef typename apply2<
              Op
            , T1
            , typename T2::type
            >::type type;
    };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_FOLD_OP_HPP_INCLUDED
