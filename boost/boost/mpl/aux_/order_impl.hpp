
#ifndef BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED

// + file: boost/mpl/aux_/order_impl.hpp
// + last modified: 03/may/03

// Copyright (c) 2002-03
// David Abrahams, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/order_fwd.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"

namespace boost {
namespace mpl {

// no default implementation; the definition is needed to make MSVC happy 

template< typename Tag > struct order_impl
{
    template< typename AssociativeSequence, typename Key > struct apply;
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,order_impl)

}}

#endif // BOOST_MPL_AUX_ORDER_IMPL_HPP_INCLUDED
