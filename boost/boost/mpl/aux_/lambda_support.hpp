//-----------------------------------------------------------------------------
// boost mpl/aux_/lambda_support.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
#define BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED

#include "boost/mpl/aux_/config/lambda.hpp"

#if !defined(BOOST_MPL_NO_FULL_LAMBDA_SUPPORT)

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i,name,params) /**/

#else

#   include "boost/mpl/aux_/preprocessor/params.hpp"
#   include "boost/preprocessor/tuple/to_list.hpp"
#   include "boost/preprocessor/list/for_each_i.hpp"
#   include "boost/preprocessor/inc.hpp"
#   include "boost/preprocessor/cat.hpp"

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC(R,typedef_,i,param) \
    typedef_ param BOOST_PP_CAT(arg,BOOST_PP_INC(i)); \
    /**/

#   define BOOST_MPL_AUX_LAMBDA_SUPPORT(i,name,params) \
    struct rebind \
    { \
        BOOST_STATIC_CONSTANT(int, arity = i); \
        BOOST_PP_LIST_FOR_EACH_I_R( \
              1 \
            , BOOST_MPL_AUX_LAMBDA_SUPPORT_ARG_TYPEDEF_FUNC \
            , typedef \
            , BOOST_PP_TUPLE_TO_LIST(i,params) \
            ) \
        \
        template< BOOST_MPL_PP_PARAMS(i,typename U) > struct apply \
        { \
            typedef typename name< BOOST_MPL_PP_PARAMS(i,U) >::type type; \
        }; \
    }; \
    /**/

#endif // BOOST_MPL_NO_FULL_LAMBDA_SUPPORT

#endif // BOOST_MPL_AUX_LAMBDA_SUPPORT_HPP_INCLUDED
