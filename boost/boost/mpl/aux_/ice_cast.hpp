//-----------------------------------------------------------------------------
// boost mpl/aux_/ice_cast.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED
#define BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED

#include "boost/mpl/aux_/config/workaround.hpp"

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
 || BOOST_WORKAROUND(__GNUC__, < 3)
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) (T)(expr)
#elif BOOST_WORKAROUND(__MWERKS__, <= 0x3001)
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) (T)(expr)
#else
#   define BOOST_MPL_AUX_ICE_CAST(T, expr) static_cast<T>(expr)
#endif

#endif // BOOST_MPL_AUX_ICE_CAST_HPP_INCLUDED
