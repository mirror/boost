//-----------------------------------------------------------------------------
// boost mpl/aux_/lambda_expr.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED

#include "boost/mpl/aux_/config/lambda.hpp"

#if defined(BOOST_MPL_NO_LAMBDA_HEURISTIC)
#   define BOOST_MPL_AUX_IS_LAMBDA_EXPR(value) /**/
#else
#   define BOOST_MPL_AUX_IS_LAMBDA_EXPR(value) \
    typedef value is_le; \
    /**/
#endif

#endif // BOOST_MPL_AUX_LAMBDA_EXPR_HPP_INCLUDED
