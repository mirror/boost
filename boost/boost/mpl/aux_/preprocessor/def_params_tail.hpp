//-----------------------------------------------------------------------------
// boost mpl/aux_/preprocessor/def_params_tail.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED
#define BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED

#include "boost/mpl/limits/arity.hpp"

// BOOST_MPL_PP_DEF_PARAMS_TAIL(1,T): , T1 = void_, .., Tn = void_
// BOOST_MPL_PP_DEF_PARAMS_TAIL(2,T): , T2 = void_, .., Tn = void_
// BOOST_MPL_PP_DEF_PARAMS_TAIL(n,T): <nothing>

#if !defined(BOOST_MPL_NO_OWN_PP_PRIMITIVES)

#   include "boost/mpl/aux_/preprocessor/filter_params.hpp"
#   include "boost/mpl/aux_/preprocessor/sub.hpp"

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL(i,param) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1( \
          i \
        , BOOST_MPL_PP_SUB(BOOST_MPL_METAFUNCTION_MAX_ARITY,i) \
        , param \
        ) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_1(i,n,p) \
    BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i,n,p) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_DELAY_2(i,n,p) \
    , BOOST_MPL_PP_DEF_PARAMS_TAIL_##i(n,p) \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_1(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##2=void_,p##3=void_,p##4=void_,p##5=void_,p##6=void_,p##7=void_,p##8=void_,p##9=void_,p1)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_2(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##3=void_,p##4=void_,p##5=void_,p##6=void_,p##7=void_,p##8=void_,p##9=void_,p1,p2)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_3(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##4=void_,p##5=void_,p##6=void_,p##7=void_,p##8=void_,p##9=void_,p1,p2,p3)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_4(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##5=void_,p##6=void_,p##7=void_,p##8=void_,p##9=void_,p1,p2,p3,p4)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_5(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##6=void_,p##7=void_,p##8=void_,p##9=void_,p1,p2,p3,p4,p5)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_6(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##7=void_,p##8=void_,p##9=void_,p1,p2,p3,p4,p5,p6)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_7(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##8=void_,p##9=void_,p1,p2,p3,p4,p5,p6,p7)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_8(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p##9=void_,p1,p2,p3,p4,p5,p6,p7,p8)
#   define BOOST_MPL_PP_DEF_PARAMS_TAIL_9(i,p) BOOST_MPL_PP_FILTER_PARAMS_##i(p1,p2,p3,p4,p5,p6,p7,p8,p9)

#else

#   include "boost/preprocessor/arithmetic/add.hpp"
#   include "boost/preprocessor/arithmetic/sub.hpp"
#   include "boost/preprocessor/tuple/elem.hpp"
#   include "boost/preprocessor/repeat.hpp"
#   include "boost/preprocessor/cat.hpp"

#   define BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC(i, op) \
    , BOOST_PP_CAT( \
          BOOST_PP_TUPLE_ELEM(2, 1, op) \
        , BOOST_PP_ADD_D(1, i, BOOST_PP_TUPLE_ELEM(2, 0, op)) \
        ) = void_ \
    /**/

#   define BOOST_MPL_PP_DEF_PARAMS_TAIL(i, param) \
    BOOST_PP_REPEAT_1ST( \
          BOOST_PP_SUB_D(1, BOOST_MPL_METAFUNCTION_MAX_ARITY, i) \
        , BOOST_MPL_PP_AUX_TAIL_PARAM_FUNC \
        , (i, param) \
        ) \
    /**/

#endif // BOOST_MPL_NO_OWN_PP_PRIMITIVES

#endif // BOOST_MPL_AUX_PREPROCESSOR_DEF_PARAMS_TAIL_HPP_INCLUDED
