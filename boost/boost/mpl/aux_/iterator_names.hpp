//-----------------------------------------------------------------------------
// boost mpl/aux_/iterator_names.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ITERATOR_NAMES_HPP_INCLUDED
#define BOOST_MPL_AUX_ITERATOR_NAMES_HPP_INCLUDED

#include "boost/config.hpp"

#if !defined(BOOST_MSVC) || BOOST_MSVC > 1300
#   define BOOST_MPL_AUX_ITERATOR_ADVANCE advance
#   define BOOST_MPL_AUX_ITERATOR_DISTANCE distance
#else
#   define BOOST_MPL_AUX_ITERATOR_ADVANCE advance_
#   define BOOST_MPL_AUX_ITERATOR_DISTANCE distance_
#endif

#endif // BOOST_MPL_AUX_ITERATOR_NAMES_HPP_INCLUDED
