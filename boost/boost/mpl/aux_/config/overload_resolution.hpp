
#ifndef BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED

// + file: boost/mpl/aux_/config/overload_resolution.hpp
// + last modified: 23/jun/03

// Copyright (c) 2002-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/config/workaround.hpp"

#if    !defined(BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
        || BOOST_WORKAROUND(__MWERKS__, < 0x3001) \
        )

#   define BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION

#endif

#endif // BOOST_MPL_AUX_CONFIG_OVERLOAD_RESOLUTION_HPP_INCLUDED
