//-----------------------------------------------------------------------------
// boost variant/detail/enable_if.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_DETAIL_ENABLE_IF_HPP
#define BOOST_VARIANT_DETAIL_ENABLE_IF_HPP

#include "boost/variant/detail/config.hpp"

///////////////////////////////////////////////////////////////////////////////
// enable_if, enable_if_c
//
// Temporary -- until boost::enable_if is adopted.
//

#if !defined(BOOST_VARIANT_AUX_NO_SFINAE)

namespace boost { namespace detail { namespace variant {

template <bool Cond, typename T = void>
struct enable_if_c
{
};

template <typename T>
struct enable_if_c< true,T >
{
    typedef T type;
};

template <typename C, typename T = void>
struct enable_if
    : enable_if_c< C::value, T >
{
};

}}} // namespace boost::detail::variant

#endif // !defined(BOOST_VARIANT_AUX_NO_SFINAE)

#endif // BOOST_VARIANT_DETAIL_ENABLE_IF_HPP
