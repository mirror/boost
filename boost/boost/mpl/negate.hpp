
#ifndef BOOST_MPL_NEGATE_HPP_INCLUDED
#define BOOST_MPL_NEGATE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct negate_impl;

template< typename T > struct negate_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct negate
#if !defined(BOOST_MPL_CFG_MSVC_ETI_BUG)
    : negate_impl<
          typename negate_tag<N>::type
        >::template apply<N>::type
#else
    : aux::msvc_eti_base< typename apply_wrap1<
          negate_impl< typename negate_tag<N>::type >
        , N
        >::type >::type
#endif
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, negate, (N))
};

BOOST_MPL_AUX_NA_SPEC(1, negate)


#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace aux {
template< typename T, T n > struct msvc_negate_impl
{
    enum msvc_wknd { value = -n };
    typedef integral_c<T,value> type;
};
}
#endif

template<>
struct negate_impl<integral_c_tag>
{
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    template< typename N > struct apply
        : aux::msvc_negate_impl< typename N::value_type, N::value >
#else
    template< typename N > struct apply
        : integral_c< typename N::value_type, (-N::value) >
#endif    
    {
    };
};

}}

#endif // BOOST_MPL_NEGATE_HPP_INCLUDED
