//-----------------------------------------------------------------------------
// boost mpl/aux_/config/eti.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED

#include "boost/config.hpp"

// flags for MSVC 6.5's so-called "early template instantiation bug"
#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
#   if BOOST_MSVC < 1300
#       define BOOST_MPL_MSVC_60_ETI_BUG
#   endif
#   define BOOST_MPL_MSVC_ETI_BUG
#endif

#endif // BOOST_MPL_AUX_CONFIG_ETI_HPP_INCLUDED
