//-----------------------------------------------------------------------------
// boost mpl/aux_/value_wknd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED

#include "boost/mpl/aux_/config/eti.hpp"

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) \
 || defined(BOOST_MPL_MSVC_60_ETI_BUG)
 
#   include "boost/mpl/int.hpp"

namespace boost { namespace mpl { namespace aux {

template< typename C_ >
struct value_wknd
    : C_
{
};

#if defined(BOOST_MPL_MSVC_60_ETI_BUG)
template<>
struct value_wknd<int>
    : int_<1>
{
};
#endif

}}} // namespace boost::mpl::aux

#   if !defined(BOOST_MPL_MSVC_60_ETI_BUG)
#       define BOOST_MPL_AUX_VALUE_WKND(C) ::boost::mpl::aux::value_wknd< C >
#       define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) BOOST_MPL_AUX_VALUE_WKND(C)
#   else
#       define BOOST_MPL_AUX_VALUE_WKND(C) C
#       define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) ::boost::mpl::aux::value_wknd< C >
#   endif

#else

#   define BOOST_MPL_AUX_VALUE_WKND(C) C
#   define BOOST_MPL_AUX_MSVC_VALUE_WKND(C) C

#endif // __BORLANDC__ || BOOST_MPL_MSVC_60_ETI_BUG

#endif // BOOST_MPL_AUX_VALUE_WKND_HPP_INCLUDED
