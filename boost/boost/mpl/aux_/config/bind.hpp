//-----------------------------------------------------------------------------
// boost mpl/aux_/config/bind.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// David Abrahams, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED

#include "boost/config.hpp"

#if    !defined(BOOST_MPL_NO_BIND_TEMPLATE) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(BOOST_MSVC) && BOOST_MSVC <= 1300 \
        || defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) \
        )

#   define BOOST_MPL_NO_BIND_TEMPLATE

#endif 

#endif // BOOST_MPL_AUX_CONFIG_BIND_HPP_INCLUDED
