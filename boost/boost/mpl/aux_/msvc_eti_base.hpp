//-----------------------------------------------------------------------------
// boost mpl/aux_/msvc_msvc_eti_base.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED

#include "boost/mpl/aux_/config/eti.hpp"
#include "boost/mpl/aux_/is_msvc_eti_arg.hpp"

namespace boost { namespace mpl { namespace aux {

#if defined(BOOST_MPL_MSVC_ETI_BUG)

template< bool > struct msvc_eti_base_impl
{
    template< typename T > struct result_
    {
        typedef T type;
    };
};

template<> struct msvc_eti_base_impl<true>
{
    template< typename T > struct result_
    {
        typedef result_ type;
    };
};

template< typename T > struct msvc_eti_base
    : msvc_eti_base_impl< is_msvc_eti_arg<T>::value >
        ::template result_<T>
{
};

#else

template< typename T > struct msvc_eti_base
{
    typedef T type;
};

#endif // BOOST_MPL_MSVC_ETI_BUG

}}} // namespace boost::mpl::aux

#endif // BOOST_MPL_AUX_MSVC_ETI_BASE_HPP_INCLUDED
