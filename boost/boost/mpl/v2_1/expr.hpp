//-----------------------------------------------------------------------------
// boost mpl/v2_1/expr.hpp header file
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

#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_EXPR_V2_1_HPP_INCLUDED
#define BOOST_MPL_EXPR_V2_1_HPP_INCLUDED

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include "boost/mpl/v2_1/expr_fwd.hpp"
#   include "boost/mpl/bind.hpp"
#endif

#if 0//defined(BOOST_MPL_USE_PREPROCESSED_HEADERS) && 
    //!defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER expr.hpp
#   include "boost/mpl/aux_/include_preprocessed.hpp"

#else

#   include "boost/mpl/limits/arity.hpp"
#   include "boost/mpl/aux_/preprocessor/params.hpp"
#   include "boost/mpl/aux_/preprocessor/repeat.hpp"
#   include "boost/preprocessor/iterate.hpp"
#   include "boost/preprocessor/comma_if.hpp"
#   include "boost/preprocessor/inc.hpp"
#   include "boost/preprocessor/cat.hpp"

namespace boost { namespace mpl { namespace v2_1 {

#   define AUX_EXPR_PARAMS(n, param) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/

#   define AUX_EXPR_SPEC_PARAMS(n, F, param) \
    F BOOST_PP_COMMA_IF(n) \
    BOOST_MPL_PP_PARAMS(n, param) \
    /**/


template< typename T > struct expr
{
    typedef T type;
};


#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, BOOST_MPL_METAFUNCTION_MAX_ARITY, "boost/mpl/v2_1/expr.hpp"))
#include BOOST_PP_ITERATE()


#   undef AUX_EXPR_SPEC_PARAMS
#   undef AUX_EXPR_PARAMS

}}} // namespace boost::mpl::v2_1

#endif // BOOST_MPL_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_EXPR_V2_1_HPP_INCLUDED

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1
#define n BOOST_PP_FRAME_ITERATION(1)

template<
      AUX_EXPR_SPEC_PARAMS(n, typename F, typename T)
    >
struct expr< F (*)(AUX_EXPR_PARAMS(n, T)) >
{
#   define AUX_EXPR_INVOCATION(unused, n, T) \
    BOOST_PP_COMMA_IF(n) \
    typename expr< BOOST_PP_CAT(T, BOOST_PP_INC(n)) >::type \
    /**/

    typedef BOOST_PP_CAT(bind,n)<
          F
        BOOST_PP_COMMA_IF(n) BOOST_MPL_PP_REPEAT(n, AUX_EXPR_INVOCATION, T)
        > type;

#   undef AUX_EXPR_INVOCATION
};

template<
      AUX_EXPR_SPEC_PARAMS(n, typename F, typename T)
    >
struct expr< F (AUX_EXPR_PARAMS(n, T)) >
    : expr< F (*)(AUX_EXPR_PARAMS(n, T)) >
{
};

#undef n
#endif // BOOST_PP_IS_ITERATING
