//-----------------------------------------------------------------------------
// boost mpl/aux_/copy_op.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_COPY_OP_HPP_INCLUDED
#define BOOST_MPL_AUX_COPY_OP_HPP_INCLUDED

#include "boost/mpl/apply.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"

namespace boost {
namespace mpl {
namespace aux {

// hand-written version is more efficient than bind/lambda expression
template<
      typename Operation
    >
struct copy_op
{
    template< typename Sequence, typename T > struct apply
    {
        typedef typename apply2<
              Operation
            , Sequence
            , T
            >::type type;
    };
};

} // namespace aux

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1,aux::copy_op)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_COPY_OP_HPP_INCLUDED
