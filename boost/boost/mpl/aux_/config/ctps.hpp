//-----------------------------------------------------------------------------
// boost mpl/aux_/config/ctps.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED

#include "boost/config.hpp"

#if    !defined(BOOST_NO_NON_TYPE_TEMPLATE_PARTIAL_SPECIALIZATION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) 

#   define BOOST_NO_NON_TYPE_TEMPLATE_PARTIAL_SPECIALIZATION

#endif

// BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION is defined in "boost/config.hpp"

#endif // BOOST_MPL_AUX_CONFIG_CTPS_HPP_INCLUDED
