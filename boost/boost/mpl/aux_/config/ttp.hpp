//-----------------------------------------------------------------------------
// boost mpl/aux_/config/ttp.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED

#include "boost/config.hpp"

#if     defined(BOOST_NO_TEMPLATE_TEMPLATES) \
     && ( !defined(BOOST_MSVC) || BOOST_MSVC < 1300 )

#   define BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif


#if    !defined(BOOST_EXTENDED_TEMPLATE_PARAMETERS_MATCHING) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && (   defined(__GNUC__)  && !defined(__EDG_VERSION__) && (__GNUC__ < 3 || __GNUC__ == 3 && __GNUC_MINOR__ <= 2 \
            || !defined(BOOST_STRICT_CONFIG)) \
        || defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) \
        )

#   define BOOST_EXTENDED_TEMPLATE_PARAMETERS_MATCHING

#endif

#endif // BOOST_MPL_AUX_CONFIG_TTP_HPP_INCLUDED
