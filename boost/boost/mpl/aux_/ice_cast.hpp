//-----------------------------------------------------------------------------
// boost mpl/aux_/ice_cast.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) \
 || defined(__GNUC__) && __GNUC__ < 3
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) expr
#elif defined(__MWERKS__) && __MWERKS__ <= 0x3001
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED
