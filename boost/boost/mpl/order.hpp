
#ifndef BOOST_MPL_ORDER_HPP_INCLUDED
#define BOOST_MPL_ORDER_HPP_INCLUDED

// + file: boost/mpl/order.hpp
// + last modified: 02/may/03

// Copyright (c) 2002-03
// David Abrahams, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/order_fwd.hpp"
#include "boost/mpl/aux_/order_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Key)
    >
struct order
    : order_impl< typename BOOST_MPL_AUX_SEQUENCE_TAG(AssociativeSequence) >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,order,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_VOID_SPEC(2, order)

}}

#endif // BOOST_MPL_ORDER_HPP_INCLUDED
