//-----------------------------------------------------------------------------
// boost mpl/aux_/config/vector.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_VECTOR_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_VECTOR_HPP_INCLUDED

// agurt, 10/jul/02: full-fledged __typeof is needed to permit the optimal 
// vector implementation

#if    !defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(__MWERKS__) && __MWERKS__ >= 0x3001
    
#   define BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL

#endif

#endif // BOOST_MPL_AUX_CONFIG_VECTOR_HPP_INCLUDED
