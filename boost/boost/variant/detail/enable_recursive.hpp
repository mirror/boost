
#if !defined(BOOST_PP_IS_ITERATING)

///// header body

//-----------------------------------------------------------------------------
// boost variant/detail/enable_recursive.hpp header file
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

#ifndef BOOST_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP
#define BOOST_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP

#include "boost/mpl/aux_/config/ctps.hpp"

#include "boost/variant/detail/enable_recursive_fwd.hpp"
#include "boost/variant/variant_fwd.hpp"

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)
#   include "boost/mpl/aux_/lambda_arity_param.hpp"
#   include "boost/mpl/aux_/template_arity.hpp"
#   include "boost/mpl/aux_/preprocessor/params.hpp"
#   include "boost/mpl/aux_/preprocessor/repeat.hpp"
#   include "boost/mpl/int_fwd.hpp"
#   include "boost/preprocessor/cat.hpp"
#   include "boost/preprocessor/arithmetic/inc.hpp"
#   include "boost/preprocessor/iterate.hpp"
#else
#   include "boost/mpl/apply.hpp"
#   include "boost/mpl/apply_if.hpp"
#   include "boost/mpl/lambda.hpp"
#endif

#include "boost/mpl/bool_fwd.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/or.hpp"
#include "boost/type_traits/is_same.hpp"

#include "boost/incomplete.hpp"

namespace boost {
namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) class specialization template enable_recursive_impl
//
// Performs recursive variant substitution.
//

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

template <
      typename T, typename RecursiveVariant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = mpl::int_< mpl::aux::template_arity<T>::value >
        )
    >
struct enable_recursive_impl
{
    typedef T type;
};

template <typename RecursiveVariant>
struct enable_recursive_impl< recursive_variant_, RecursiveVariant > 
{
    typedef RecursiveVariant type;
};

#define BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL(N) \
    typedef typename enable_recursive_impl<   \
          BOOST_PP_CAT(U,N), RecursiveVariant \
        >::type BOOST_PP_CAT(u,N);            \
    /**/

#define BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF(z, N, _) \
    BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL( BOOST_PP_INC(N) ) \
    /**/

#define BOOST_PP_ITERATION_LIMITS (1,BOOST_VARIANT_RECURSIVE_VARIANT_MAX_ARITY)
#define BOOST_PP_FILENAME_1 "boost/variant/detail/enable_recursive.hpp"
#include BOOST_PP_ITERATE()

#undef BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF_IMPL
#undef BOOST_VARIANT_AUX_ENABLE_RECURSIVE_TYPEDEF

#else // defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

template <typename T, typename U1>
struct rebind1
{
private:
    typedef typename mpl::lambda<
          mpl::identity<T>
        >::type le_;

public:
    typedef typename mpl::apply_if<
          is_same< le_, mpl::identity<T> >
        , le_ // identity<T>
        , mpl::apply1<le_, U1>
        >::type type;
};

template <typename T, typename RecursiveVariant>
struct enable_recursive_impl
    : rebind1< T,RecursiveVariant >
{
};

#endif // !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction enable_recursive
//
// Attempts recursive variant substitution and wraps with boost::incomplete
// if substituion occurs *and* NoWrapper is false_.
//

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T, typename RecursiveVariant, typename NoWrapper>
struct enable_recursive
    : enable_recursive_impl<T,RecursiveVariant>
{
};

template <typename T, typename RecursiveVariant>
struct enable_recursive< T,RecursiveVariant,mpl::false_ >
{
private: // helpers, for metafunction result (below)

    typedef typename enable_recursive_impl<T,RecursiveVariant>::type t_;

public: // metafunction result

    // [Wrap with incomplete only if rebind really changed something:]
    typedef typename mpl::if_<
          is_same< t_,T >
        , t_
        , boost::incomplete<t_>
        >::type type;

};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T, typename RecursiveVariant, typename NoWrapper>
struct enable_recursive
{
private: // helpers, for metafunction result (below)

    typedef typename enable_recursive_impl<T,RecursiveVariant>::type t_;

public: // metafunction result

    // [Wrap with incomplete only if rebind really changed something:]
    typedef typename mpl::if_<
          mpl::or_< NoWrapper, is_same< t_,T > >
        , t_
        , boost::incomplete<t_>
        >::type type;

};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction class quoted_enable_recursive
//
// Same behavior as enable_recursive metafunction (see above).
//
template <typename RecursiveVariant, typename NoWrapper>
struct quoted_enable_recursive
{
    template <typename T>
    struct apply
        : enable_recursive<T, RecursiveVariant, NoWrapper>
    {
    };
};

}} // namespace detail::variant
} // namespace boost

#endif // BOOST_VARIANT_DETAIL_ENABLE_RECURSIVE_HPP

///// iteration, depth == 1

#elif BOOST_PP_ITERATION_DEPTH() == 1
#define i BOOST_PP_FRAME_ITERATION(1)

template <
      template < BOOST_MPL_PP_PARAMS(i,typename P) > class T
    , BOOST_MPL_PP_PARAMS(i,typename U)
    , typename RecursiveVariant
    >
struct enable_recursive_impl<
      T< BOOST_MPL_PP_PARAMS(i,U) >
    , RecursiveVariant
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
