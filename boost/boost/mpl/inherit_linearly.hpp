//-----------------------------------------------------------------------------
// boost mpl/inherit_linearly.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
#define BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED

#include "boost/mpl/fold.hpp"
#include "boost/mpl/empty_base.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Types_)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Node_)
    , typename Root_ = empty_base
    >
struct inherit_linearly
    : fold<Types_,Root_,Node_>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,inherit_linearly,(Types_,Node_,Root_))
};

BOOST_MPL_AUX_VOID_SPEC(2, inherit_linearly)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_INHERIT_FRONT_TO_BACK_HPP_INCLUDED
