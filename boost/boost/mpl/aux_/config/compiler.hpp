//-----------------------------------------------------------------------------
// boost mpl/aux_/config/dtp.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED

#include "boost/mpl/aux_/config/dtp.hpp"
#include "boost/mpl/aux_/config/ttp.hpp"
#include "boost/config.hpp"

#if defined(BOOST_MSVC) && BOOST_MSVC < 1300
#   define BOOST_MPL_COMPILER_DIR msvc60

#elif defined(BOOST_MSVC) && BOOST_MSVC == 1300
#   define BOOST_MPL_COMPILER_DIR msvc70

#elif defined(__GNUC__) && !defined(__EDG_VERSION__)
#   define BOOST_MPL_COMPILER_DIR gcc

#elif defined(__BORLANDC__) 
#   if !defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)
#       define BOOST_MPL_COMPILER_DIR bcc551
#   else
#       define BOOST_MPL_COMPILER_DIR bcc
#   endif

#elif defined(__MWERKS__) 
#   if defined(BOOST_BROKEN_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)
#       define BOOST_MPL_COMPILER_DIR mwcw
#   else
#       define BOOST_MPL_COMPILER_DIR plain
#   endif

#elif defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   define BOOST_MPL_COMPILER_DIR no_ctps

#elif defined(BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS)
#   define BOOST_MPL_COMPILER_DIR no_ttp

#else
#   define BOOST_MPL_COMPILER_DIR plain
#endif

#endif // BOOST_MPL_AUX_CONFIG_COMPILER_HPP_INCLUDED
