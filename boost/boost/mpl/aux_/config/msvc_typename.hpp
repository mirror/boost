//-----------------------------------------------------------------------------
// boost mpl/aux_/config/msvc_typename.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1300)
#   define BOOST_MSVC_TYPENAME
#else
#   define BOOST_MSVC_TYPENAME typename
#endif

#endif // BOOST_MPL_AUX_CONFIG_MSVC_TYPENAME_HPP_INCLUDED
