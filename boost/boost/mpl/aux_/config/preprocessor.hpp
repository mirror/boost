
#ifndef BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED

// + file: boost/mpl/aux_/config/preprocessor.hpp
// + last modified: 02/sep/03

// Copyright (C) 2000-03 Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/config/workaround.hpp"

#if    BOOST_WORKAROUND(__MWERKS__, <= 0x3003) \
    || BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(502))

#   define BOOST_MPL_BROKEN_PP_MACRO_EXPANSION

#endif

//#define BOOST_MPL_NO_OWN_PP_PRIMITIVES

#endif // BOOST_MPL_AUX_CONFIG_PREPROCESSOR_HPP_INCLUDED
