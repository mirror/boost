//-----------------------------------------------------------------------------
// boost mpl/arithmetic/modulus.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2111%12
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_ARITHMETIC_MODULUS_HPP_INCLUDED
#define BOOST_MPL_ARITHMETIC_MODULUS_HPP_INCLUDED

#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/typeof.hpp"
#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
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

#if defined(BOOST_MPL_MSVC_70_ETI_BUG)
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
        , BOOST_MPL_AUX_VALUE_WKND(T1)::value
        , BOOST_MPL_AUX_VALUE_WKND(T2)::value
        >
{
};

BOOST_MPL_AUX_VOID_SPEC(2,modulus)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ARITHMETIC_MODULUS_HPP_INCLUDED
