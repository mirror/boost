
#ifndef BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/gcc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

// agurt, 03/may/03: when defining 'friend' operators, use specialization
// in place of conventional overloading to supress a warning on GCC 3.x;
// breaks 2.95.x!
#if !defined(BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION) \
    && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, > 0x0295) \
    && BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, BOOST_TESTED_AT(0x0302))

#   define BOOST_MPL_CFG_USE_OPERATORS_SPECIALIZATION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OPERATORS_HPP_INCLUDED
