//-----------------------------------------------------------------------------
// boost mpl/aux_/config/use_preprocessed.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_INTERNALS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_INTERNALS_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(BOOST_MSVC) && BOOST_MSVC < 1300 \
 && !defined(BOOST_MPL_INTERNALS_USE_ITERATOR_CATEGORY)
#   define BOOST_MPL_INTERNALS_USE_ITERATOR_CATEGORY
#endif

#endif // BOOST_MPL_AUX_CONFIG_INTERNALS_HPP_INCLUDED
