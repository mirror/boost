
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

//-----------------------------------------------------------------------------
// boost variant/recursive_variant.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_RECURSIVE_VARIANT_HPP
#define BOOST_VARIANT_RECURSIVE_VARIANT_HPP

#include "boost/variant/detail/enable_recursive_stub.hpp"
#include "boost/incomplete.hpp" // only forward-declared in stub header

#include "boost/mpl/limits/arity.hpp"
#include "boost/mpl/arg.hpp"

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)
#   include "boost/mpl/aux_/lambda_arity_param.hpp"
#   include "boost/mpl/int_fwd.hpp"
#   include "boost/mpl/aux_/preprocessor/params.hpp"
#   include "boost/mpl/aux_/preprocessor/repeat.hpp"
#   include "boost/preprocessor/arithmetic/inc.hpp"
#   include "boost/preprocessor/iterate.hpp"
#endif


///////////////////////////////////////////////////////////////////////////////
// (detail) macro BOOST_VARIANT_RECURSIVE_VARIANT_MAX_ARITY
//
// Exposes maximum allowed arity of class templates with recursive_variant
// arguments. (That is, variant< ..., T<[1], recursive_variant, ... [N]> >.)
//
#define BOOST_VARIANT_RECURSIVE_VARIANT_MAX_ARITY \
    BOOST_MPL_METAFUNCTION_MAX_ARITY

namespace boost {

///////////////////////////////////////////////////////////////////////////////
// type recursive_variant
//
// Tag type indicates where recursive variant substitution should occur.
//
typedef mpl::arg<1>
    recursive_variant;

///////////////////////////////////////////////////////////////////////////////
// (detail) class specialization template enable_recursive_impl
//
// Enables recursive variant substitution.
//

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

namespace detail { namespace variant {

template <typename Variant>
struct enable_recursive_impl< recursive_variant, Variant > 
{
    typedef Variant type;
};

#define BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL(N) \
    typedef typename enable_recursive_impl< \
          BOOST_PP_CAT(U,N), Variant \
        >::type BOOST_PP_CAT(u,N); \
    /**/

#define BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF(z, N, _) \
    BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL( BOOST_PP_INC(N) ) \
    /**/

#define BOOST_PP_ITERATION_LIMITS (1,BOOST_VARIANT_RECURSIVE_VARIANT_MAX_ARITY)
#define BOOST_PP_FILENAME_1 "boost/variant/recursive_variant.hpp"
#include BOOST_PP_ITERATE()

#undef BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL
#undef BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF

}} // namespace detail::variant

#else // defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

//
// see detail/enable_recursive_stub.hpp for workaround.
//

#endif // !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

} // namespace boost

#endif // BOOST_VARIANT_RECURSIVE_VARIANT_HPP

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1
#define i BOOST_PP_FRAME_ITERATION(1)

template <
      template < BOOST_MPL_PP_PARAMS(i,typename P) > class T
    , BOOST_MPL_PP_PARAMS(i,typename U)
    , typename Variant
    >
struct enable_recursive_impl<
      T< BOOST_MPL_PP_PARAMS(i,U) >
    , Variant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(mpl::int_<( i )>)
    >
{
private:
    BOOST_MPL_PP_REPEAT(i, BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF, _)

public:
    typedef T< BOOST_MPL_PP_PARAMS(i,u) > type;
};

#undef i
#endif // BOOST_PP_IS_ITERATING
