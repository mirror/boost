//-----------------------------------------------------------------------------
// boost mpl/vector/aux_/numbered_c.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// no include guards, the header is intended for multiple inclusion!

#if defined(BOOST_PP_IS_ITERATING)

#include "boost/preprocessor/enum_params.hpp"
#include "boost/preprocessor/enum_shifted_params.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/dec.hpp"
#include "boost/preprocessor/cat.hpp"

#define i BOOST_PP_FRAME_ITERATION(1)

#if defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL)

#   define MPL_AUX_VECTOR_TAIL(vector, i, C) \
    BOOST_PP_CAT(BOOST_PP_CAT(vector,BOOST_PP_DEC(i)),_c)<T \
      BOOST_PP_COMMA_IF(BOOST_PP_DEC(i)) BOOST_PP_ENUM_SHIFTED_PARAMS(i, C) \
    > \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i),_c)
    : vector_node<
          i
        , integral_c<T,C0>
        , MPL_AUX_VECTOR_TAIL(vector,i,C)
        >
{
};

#   undef MPL_AUX_VECTOR_TAIL

#else // "brute force" implementation

#   define MPL_AUX_VECTOR_C_PARAM_FUNC(unused, i, param) \
    BOOST_PP_COMMA_IF(i) \
    integral_c<T,BOOST_PP_CAT(param,i)> \
    /**/

template<
      typename T
    , BOOST_PP_ENUM_PARAMS(i, T C)
    >
struct BOOST_PP_CAT(BOOST_PP_CAT(vector,i),_c)
    : BOOST_PP_CAT(vector,i)< BOOST_PP_REPEAT_1(i,MPL_AUX_VECTOR_C_PARAM_FUNC,C) >
{
};

#   undef MPL_AUX_VECTOR_C_PARAM_FUNC

#endif // BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL

#undef i

#endif // BOOST_PP_IS_ITERATING
