//-----------------------------------------------------------------------------
// boost mpl/copy_backward.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_COPY_BACKWARD_HPP_INCLUDED
#define BOOST_MPL_COPY_BACKWARD_HPP_INCLUDED

#include "boost/mpl/fold_backward.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/algorithm_namespace.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(State)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(BinaryOp)
    >
struct copy_backward
    : fold_backward< Sequence,State,BinaryOp >
{
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END
BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(3, copy_backward)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_COPY_BACKWARD_HPP_INCLUDED
