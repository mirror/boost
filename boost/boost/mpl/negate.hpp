
#ifndef BOOST_MPL_NEGATE_HPP_INCLUDED
#define BOOST_MPL_NEGATE_HPP_INCLUDED

// + file: boost/mpl/negate.hpp
// + last modified: 25/feb/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/typeof.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct negate
{
    typedef BOOST_MPL_AUX_TYPEOF(T,T::value) value_type;
    BOOST_STATIC_CONSTANT(value_type, value = (-T::value));
#if !defined(__BORLANDC__)
    typedef integral_c<value_type, value> type;
#else
    typedef integral_c<value_type, (-T::value)> type;
#endif

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, negate, (T))
};

BOOST_MPL_AUX_VOID_SPEC(1,negate)

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_NEGATE_HPP_INCLUDED
