//-----------------------------------------------------------------------------
// boost mpl/aux_/sequence_tag.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_SEQUENCE_TAG_HPP_INCLUDED
#define BOOST_MPL_AUX_SEQUENCE_TAG_HPP_INCLUDED

//#include "boost/mpl/aux_/config/internal.hpp"
#include "boost/config.hpp"

#if !defined(BOOST_MPL_INTERNAL_USE_SEQUENCE_TAG)
#   define BOOST_MPL_INTERNAL_USE_SEQUENCE_TAG
#endif

#if defined(BOOST_MPL_INTERNAL_USE_SEQUENCE_TAG) \
 || defined(BOOST_MSVC) && BOOST_MSVC < 1300

#   include "boost/mpl/sequence_tag.hpp"
#   define BOOST_MPL_AUX_SEQUENCE_TAG(seq) sequence_tag<seq>::type

#else

#   define BOOST_MPL_AUX_SEQUENCE_TAG(seq) seq::tag

#endif

#endif // BOOST_MPL_AUX_SEQUENCE_TAG_HPP_INCLUDED
