//-----------------------------------------------------------------------------
// boost mpl/apply.hpp header file
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

#ifndef BOOST_MPL_APPLY_HPP_INCLUDED
#define BOOST_MPL_APPLY_HPP_INCLUDED

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)
#   include "boost/mpl/aux_/preprocessed/apply.hpp"
#else

#include "boost/mpl/placeholder.hpp"
#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/aux_/lambda_spec.hpp"
#include "boost/mpl/aux_/count_if_not.hpp"
#include "boost/mpl/aux_/arity.hpp"
#include "boost/mpl/aux_/none.hpp"
#include "boost/mpl/aux_/msvc_workarounds.hpp"
#include "boost/mpl/aux_/preprocessor/params.hpp"
#include "boost/mpl/aux_/preprocessor/default_params.hpp"
#include "boost/mpl/aux_/preprocessor/enum.hpp"
#include "boost/mpl/aux_/preprocessor/project1st.hpp"
#include "boost/mpl/aux_/config/dtp.hpp"

#include "boost/preprocessor/arithmetic/add.hpp"
#include "boost/preprocessor/arithmetic/sub.hpp"
#include "boost/preprocessor/repeat_2nd.hpp"
#include "boost/preprocessor/repeat_3rd.hpp"
#include "boost/preprocessor/comma_if.hpp"
#include "boost/preprocessor/if.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

// local macros, #undef-ined at the end of the header
#define AUX_APPLY_PARAMS(param) \
    BOOST_MPL_PP_PARAMS( \
          1 \
        , BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY) \
        , param \
        ) \
/**/

#define AUX_APPLY_DEFAULT_PARAMS(param, value) \
    BOOST_MPL_PP_DEFAULT_PARAMS( \
          1 \
        , BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY) \
        , param \
        , value \
        ) \
/**/

#define AUX_APPLY_N_PARAMS(i, param) \
    BOOST_MPL_PP_PARAMS(1, BOOST_PP_INC(i), param) \
/**/

#define AUX_APPLY_N_PLACEHOLDERS(i) \
    BOOST_MPL_PP_ENUM(0, BOOST_PP_INC(i), BOOST_MPL_PP_PROJECT2ND, _) \
/**/

#define AUX_APPLY_0_TEMPLATE_DEF(unused) \
template< typename F > \
struct apply0 : F \
{ \
}; \
\
template<> \
struct apply0<_> \
{ \
    template< typename F > struct apply \
        : F \
    { \
    }; \
}; \
/**/

#if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)

// 'apply0' workaround
template< typename F > struct apply0;
template<> struct apply0<int> { typedef apply0 type; };

#define AUX_APPLY_N_TEMPLATE_DEF(i) \
namespace aux { \
BOOST_MPL_AUX_MSVC_DEPENDENT_TEMPLATE_WRAPPER_DEF(msvc_apply##i, apply, i) \
} \
template< \
      typename F \
    , AUX_APPLY_N_PARAMS(i, typename T) \
    > \
struct apply##i \
    : aux::msvc_apply##i<F>::template result_<AUX_APPLY_N_PARAMS(i, T)> \
{ \
}; \
\
template<> \
struct apply##i< AUX_APPLY_N_PLACEHOLDERS(i) > \
{ \
    template< \
          typename F \
        , AUX_APPLY_N_PARAMS(i, typename T) \
        > \
    struct apply \
        : aux::msvc_apply##i<F>::template result_<AUX_APPLY_N_PARAMS(i, T)> \
    { \
    }; \
}; \
/**/

#elif defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)
// agurt, 10/mar/02: MWCW 8.0 "losts" default template parameters of nested 
// class templates when their owner classes are passed as arguments to 
// other templates; in particular, that means that 'apply#' won't work on
// the result of 'bind#<..>' expression if no special care is taken; 
// whatever is below, it is supposed to workaround the problem

#define AUX_APPLY_IMPL_N_TEMPLATE_SPEC(j,i) \
namespace aux { \
template< \
      typename F \
    , AUX_APPLY_N_PARAMS(i, typename T) \
    > \
struct mwcw_apply##i< \
          BOOST_PP_ADD(i, j) \
        , F \
        , AUX_APPLY_N_PARAMS(i, T) \
        > \
{ \
    typedef typename F::template apply< \
          AUX_APPLY_N_PARAMS(i, T) \
          BOOST_PP_COMMA_IF(j) \
          BOOST_MPL_PP_ENUM(0, j, BOOST_MPL_PP_PROJECT2ND, aux::none) \
         > type; \
}; \
} \
/**/

#define AUX_APPLY_N_TEMPLATE_DEF(i) \
namespace aux { \
template< \
      long \
    , typename F \
    , AUX_APPLY_N_PARAMS(i, typename T) \
    > \
struct mwcw_apply##i; \
} \
\
BOOST_PP_REPEAT_3RD( \
      BOOST_PP_INC(BOOST_PP_SUB(BOOST_MPL_METAFUNCTION_MAX_ARITY, i)) \
    , AUX_APPLY_IMPL_N_TEMPLATE_SPEC \
    , i \
    ) \
\
template< \
      typename F \
    , AUX_APPLY_N_PARAMS(i, typename T) \
    > \
struct apply##i \
    : aux::mwcw_apply##i< \
           aux::arity<F,i>::value \
         , F \
         , AUX_APPLY_N_PARAMS(i, T) \
         >::type \
{ \
}; \
\
template<> \
struct apply##i< AUX_APPLY_N_PLACEHOLDERS(i) > \
{ \
    template< \
          typename F \
        , AUX_APPLY_N_PARAMS(i, typename T) \
        > \
    struct apply \
        : aux::mwcw_apply##i< \
              aux::arity<F,i>::value \
            , F \
            , AUX_APPLY_N_PARAMS(i, T) \
            >::type \
    { \
    }; \
}; \
/**/

#else // #elif defined(BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

#define AUX_APPLY_N_TEMPLATE_DEF(i) \
template< \
      typename F \
    , AUX_APPLY_N_PARAMS(i, typename T) \
    > \
struct apply##i \
    : F::template apply< \
          AUX_APPLY_N_PARAMS(i, T) \
        > \
{ \
}; \
\
template<> \
struct apply##i< AUX_APPLY_N_PLACEHOLDERS(i) > \
{ \
    template< \
          typename F \
        , AUX_APPLY_N_PARAMS(i, typename T) \
        > \
    struct apply \
        : F::template apply< \
              AUX_APPLY_N_PARAMS(i, T) \
            > \
    { \
    }; \
}; \
/**/

#endif // #if defined(BOOST_MSVC) && (BOOST_MSVC < 1300)

namespace aux {
// to be able to define specializations
template<long> struct apply_impl_chooser;
}

#define AUX_APPLY_IMPL_CHOOSER_SPEC(i) \
namespace aux { \
template<> \
struct apply_impl_chooser<i> \
{ \
    template< typename F, AUX_APPLY_PARAMS(typename T) > \
    struct result_ \
    { \
        typedef apply##i< \
              F \
            BOOST_PP_COMMA_IF(i) AUX_APPLY_N_PARAMS(i, T) \
            > type; \
    }; \
}; \
} \
/**/

#define AUX_APPLY_TEMPLATE_DEF(i, unused) \
    BOOST_PP_IF( \
          i \
        , AUX_APPLY_N_TEMPLATE_DEF \
        , AUX_APPLY_0_TEMPLATE_DEF \
        )(i) \
    \
    BOOST_MPL_AUX_LAMBDA_TEMPLATE_SPEC( \
          BOOST_PP_INC(i) \
        , apply##i \
        ) \
    \
    AUX_APPLY_IMPL_CHOOSER_SPEC(i) \
/**/


// apply# 
BOOST_PP_REPEAT_2ND(
      BOOST_PP_INC(BOOST_MPL_METAFUNCTION_MAX_ARITY)
    , AUX_APPLY_TEMPLATE_DEF
    , unused
    )

BOOST_MPL_AUX_COUNT_IF_NOT(apply, BOOST_MPL_METAFUNCTION_MAX_ARITY)

#if !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)
// agurt, 15/jan/02: top-level 'apply' template gives an ICE on MSVC
// (for known reasons); numbered form works, though
template<
      typename F
    , AUX_APPLY_DEFAULT_PARAMS(typename T, aux::none)
    >
struct apply
    : aux::apply_impl_chooser< 
          aux::apply_count_if_not<aux::none, AUX_APPLY_PARAMS(T)>::value
        >::template result_< F, AUX_APPLY_PARAMS(T) >::type
{
};

#define BOOST_MPL_HAS_APPLY

#endif // !defined(BOOST_MSVC) || (BOOST_MSVC > 1200)

#undef AUX_APPLY_TEMPLATE_DEF
#undef AUX_APPLY_N_TEMPLATE_DEF
#undef AUX_APPLY_0_TEMPLATE_DEF
#undef AUX_APPLY_IMPL_N_TEMPLATE_SPEC
#undef AUX_APPLY_N_PLACEHOLDERS
#undef AUX_APPLY_N_PARAMS
#undef AUX_APPLY_DEFAULT_PARAMS
#undef AUX_APPLY_PARAMS

} // namespace mpl
} // namespace boost

#endif // #if defined(BOOST_MPL_USE_PREPROCESSED_HEADERS)

#endif // BOOST_MPL_APPLY_HPP_INCLUDED
