
#ifndef BOOST_MPL_MODULUS_HPP_INCLUDED
#define BOOST_MPL_MODULUS_HPP_INCLUDED

// + file: boost/mpl/modulus.hpp
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
#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/eti.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename T, T N1, T N2
    >
struct modulus_c
{
    BOOST_STATIC_CONSTANT(T, value = (N1 % N2));
#if !defined(__BORLANDC__)
    typedef integral_c<T,value> type;
#else
    typedef integral_c<T,(N1 % N2)> type;
#endif
};

#if defined(BOOST_MPL_MSVC_ETI_BUG)
template<>
struct modulus_c<long,0,0>
{
};
#endif

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    >
struct modulus
    : modulus_c<
          BOOST_MPL_AUX_TYPEOF(T1,
             T1::value % T2::value
            )
        , BOOST_MPL_AUX_MSVC_VALUE_WKND(T1)::value
        , BOOST_MPL_AUX_MSVC_VALUE_WKND(T2)::value
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, modulus, (T1,T2))
};

BOOST_MPL_AUX_VOID_SPEC(2,modulus)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_MODULUS_HPP_INCLUDED
