//-----------------------------------------------------------------------------
// boost mpl/aux_/lambda_spec.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED

#include "boost/mpl/void.hpp"
#include "boost/mpl/lambda_fwd.hpp"
#include "boost/mpl/int_fwd.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/lambda_arity_param.hpp"
#include "boost/mpl/aux_/config/lambda.hpp"

#if !defined(BOOST_MPL_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) \
template< \
      BOOST_MPL_PP_PARAMS(i, typename T) \
    , typename Tag \
    > \
struct lambda< \
      name< BOOST_MPL_PP_PARAMS(i, T) > \
    , Tag \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(int_<-1>) \
    > \
{ \
    typedef name< BOOST_MPL_PP_PARAMS(i, T) > type; \
}; \
/**/

#else

#   define BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(i, name) /**/

#endif

#endif // BOOST_MPL_AUX_LAMBDA_SPEC_HPP_INCLUDED
