//-----------------------------------------------------------------------------
// boost mpl/aux_/arg_typedef.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
#define BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED

#include "boost/mpl/aux_/config/lambda.hpp"

#if defined(BOOST_MPL_NO_FULL_LAMBDA_SUPPORT)
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) typedef T name;
#else
#   define BOOST_MPL_AUX_ARG_TYPEDEF(T, name) /**/
#endif

#endif // BOOST_MPL_AUX_ARG_TYPEDEF_HPP_INCLUDED
