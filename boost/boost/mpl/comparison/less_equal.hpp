//-----------------------------------------------------------------------------
// boost mpl/comparison/less_equal.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_COMPARISON_LESS_EQUAL_HPP_INCLUDED
#define BOOST_MPL_COMPARISON_LESS_EQUAL_HPP_INCLUDED

#include "boost/mpl/bool_c.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/aux_/value_wknd.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    >
struct less_equal
{
    BOOST_STATIC_CONSTANT(bool, value = (
          BOOST_MPL_AUX_VALUE_WKND(T1)::value 
            <= BOOST_MPL_AUX_VALUE_WKND(T2)::value
        ));

#if !defined(__BORLANDC__)
    typedef bool_c<value> type;
#else
    typedef bool_c<(
          BOOST_MPL_AUX_VALUE_WKND(T1)::value 
            <= BOOST_MPL_AUX_VALUE_WKND(T2)::value
        )> type;
#endif

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,less_equal,(T1,T2))
};

BOOST_MPL_AUX_VOID_SPEC(2, less_equal)

template< long N >
struct le
{
    template< typename T > struct apply
#if !defined(__BORLANDC__)
        : less_equal< T,integral_c<long,N> >
    {
#else
    {
        typedef typename less_equal< T,integral_c<long,N> >::type type;
#endif
    };
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_COMPARISON_LESS_EQUAL_HPP_INCLUDED
