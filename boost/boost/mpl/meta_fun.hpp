//-----------------------------------------------------------------------------
// boost mpl/meta_fun.hpp header file
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

#if !defined(BOOST_PP_IS_ITERATING)

///// header body

#ifndef BOOST_MPL_META_FUN_HPP_INCLUDED
#define BOOST_MPL_META_FUN_HPP_INCLUDED

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS) && \
    !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER meta_fun.hpp
#   include "boost/mpl/aux_/include_preprocessed.hpp"

#else

#   include "boost/mpl/limits/arity.hpp"
#   include "boost/mpl/aux_/preprocessor/params.hpp"
#   include "boost/mpl/aux_/config/ttp.hpp"

#   include "boost/preprocessor/iterate.hpp"
#   include "boost/preprocessor/cat.hpp"

#if !defined(BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS)

namespace boost {
namespace mpl {

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3,(1, BOOST_MPL_METAFUNCTION_MAX_ARITY, "boost/mpl/meta_fun.hpp"))
#include BOOST_PP_ITERATE()

} // namespace mpl
} // namespace boost

#endif // BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS

#endif // BOOST_MPL_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_META_FUN_HPP_INCLUDED

///// iteration

#else
#define i BOOST_PP_FRAME_ITERATION(1)

template<
      template< BOOST_MPL_PP_PARAMS(i, typename P) > class F
    >
struct BOOST_PP_CAT(meta_fun,i)
{
    template< BOOST_MPL_PP_PARAMS(i, typename U) > struct apply
        : F< BOOST_MPL_PP_PARAMS(i, U) >
    {
    };
};

#undef i
#endif // BOOST_PP_IS_ITERATING
