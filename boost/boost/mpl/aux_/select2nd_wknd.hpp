//-----------------------------------------------------------------------------
// boost mpl/aux_/select2nd_wknd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_SELECT2ND_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_SELECT2ND_WKND_HPP_INCLUDED

#include "boost/mpl/aux_/is_msvc_eti_arg.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

#if defined(BOOST_MPL_MSVC_ETI_BUG)

namespace boost { namespace mpl { namespace aux {

#   if defined(BOOST_MPL_MSVC_60_ETI_BUG)

template< typename Pair >
struct select2nd_wknd
{
    typedef typename Pair::second type;
};

template<> struct select2nd_wknd<int>
{
    typedef int type;
};

#   else // !defined(BOOST_MPL_MSVC_60_ETI_BUG)

template< bool > struct select2nd_wknd_impl
{
    template< typename Pair > struct result_
    {
        typedef typename Pair::second type;
    };
};

template<> struct select2nd_wknd_impl<false>
{
    template< typename Pair > struct result_
    {
        typedef int type;
    };
};

template< typename Pair > struct select2nd_wknd
    : select2nd_wknd_impl< !aux::is_msvc_eti_arg<Pair>::value >
        ::template result_<Pair>
{
};

#   endif // BOOST_MPL_MSVC_60_ETI_BUG workaround

}}} // namespace boost::mpl::aux

#   define BOOST_MPL_AUX_SELECT2ND_WKND(pair) ::boost::mpl::aux::select2nd_wknd< pair >::type

#else // !defined(BOOST_MPL_MSVC_ETI_BUG)

#   define BOOST_MPL_AUX_SELECT2ND_WKND(pair) pair::second

#endif // BOOST_MPL_MSVC_ETI_BUG workaround

#endif // BOOST_MPL_AUX_SELECT2ND_WKND_HPP_INCLUDED
