//-----------------------------------------------------------------------------
// boost variant/detail/define_forwarding_func.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_DETAIL_DEFINE_FORWARDING_FUNC_HPP
#define BOOST_VARIANT_DETAIL_DEFINE_FORWARDING_FUNC_HPP

#include "boost/preprocessor/debug/assert.hpp"
#include "boost/preprocessor/comparison/less_equal.hpp"

//////////////////////////////////////////////////////////////////////////
// BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC

// 000
// 001
// 010
// 011      'const pattern' follows binary addition...
// 100      (TODO: generalize with preprocessor to N params)
// 101
// 110
// 111

// support macros
#define BOOST_VARIANT_AUX_NOTHING /**/

#if !defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_1(macro)    \
    macro(BOOST_VARIANT_AUX_NOTHING)                         \
    macro(const)                                             \
    /**/

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_2(macro)           \
    macro(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)      \
    macro(BOOST_VARIANT_AUX_NOTHING,const)                          \
    macro(const,BOOST_VARIANT_AUX_NOTHING)                          \
    macro(const,const)                                              \
    /**/

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_3(macro)    \
    macro(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)    \
    macro(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING,const)                        \
    macro(BOOST_VARIANT_AUX_NOTHING,const,BOOST_VARIANT_AUX_NOTHING)                        \
    macro(BOOST_VARIANT_AUX_NOTHING,const,const)                                            \
    macro(const,BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)                        \
    macro(const,BOOST_VARIANT_AUX_NOTHING,const)                                            \
    macro(const,const,BOOST_VARIANT_AUX_NOTHING)                                            \
    macro(const,const,const)                                                                \
    /**/

#else // defined(BOOST_NO_FUNCTION_TEMPLATE_ORDERING)

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_1(macro)    \
    macro(BOOST_VARIANT_AUX_NOTHING)                    \
    /**/

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_2(macro)    \
    macro(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)      \
    /**/

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_3(macro)    \
    macro(BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING,BOOST_VARIANT_AUX_NOTHING)    \
    /**/

#endif

#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_IMPL_MAX 3
#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_IMPL_MAX_MSG  \
    "current implementation of BOOST_DEFINE_FORWARDING_FUNC only supports 3 params"

// actual macro definition:
#define BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC( macro , arg_count )   \
    BOOST_PP_ASSERT_MSG(                                                \
          BOOST_PP_LESS_EQUAL(                                          \
              arg_count                                                 \
            , BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_IMPL_MAX         \
            )                                                           \
        , BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_IMPL_MAX_MSG         \
        )                                                               \
    BOOST_PP_CAT(                                                       \
          BOOST_VARIANT_AUX_DEFINE_FORWARDING_FUNC_                     \
        , arg_count                                                     \
        ) (macro)                                                       \
    /**/

#endif // BOOST_VARIANT_DETAIL_DEFINE_FORWARDING_FUNC_HPP
