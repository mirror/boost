//-----------------------------------------------------------------------------
// boost variant/detail/enable_recursive_stub.hpp header file
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

#ifndef BOOST_MPL_VARIANT_DETAIL_ENABLE_RECURSIVE_STUB_HPP
#define BOOST_MPL_VARIANT_DETAIL_ENABLE_RECURSIVE_STUB_HPP

#include "boost/config.hpp"
#include "boost/mpl/aux_/config/ttp.hpp"

#include "boost/incomplete_fwd.hpp"

///////////////////////////////////////////////////////////////////////////////
// (detail) macro BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT
//
// Defined if MPL lambda facility should be used as workaround for broken
// compilers.
//
#if defined(BOOST_NO_TEMPLATE_TEMPLATE_PARAMETERS) \
 || defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
 && !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)
#   define BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT
#endif

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)
#   include "boost/mpl/aux_/template_arity.hpp"
#   include "boost/mpl/aux_/lambda_arity_param.hpp"
#   include "boost/mpl/int_fwd.hpp"
#else
#   include "boost/mpl/apply.hpp"
#   include "boost/mpl/apply_if.hpp"
#   include "boost/mpl/identity.hpp"
#   include "boost/mpl/if.hpp"
#   include "boost/mpl/lambda.hpp"
#   include "boost/type_traits/is_same.hpp"
#endif

namespace boost {
namespace detail { namespace variant {

///////////////////////////////////////////////////////////////////////////////
// (detail) metafunction enable_recursive
//
// Enables the boost::variant<..., boost::recursive_variant, ...> syntax.
//

#if !defined(BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT)

// primary template (specialized in recursive_variant.hpp)
template <
      typename T, typename Variant
      BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(
          typename Arity = mpl::int_< mpl::aux::template_arity<T>::value >
        )
    >
struct enable_recursive_impl
{
    typedef T type;
};

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

template <typename T, typename Variant>
struct enable_recursive_impl
    : rebind1< T,Variant >
{
};

#endif // BOOST_VARIANT_NO_FULL_RECURSIVE_VARIANT_SUPPORT workaround

template <typename T, typename Variant>
struct enable_recursive
{
private: // helpers, for metafunction result (below)

    typedef typename enable_recursive_impl<T,Variant>::type t_;

public: // metafunction result

    // [Wrap with incomplete only if rebind really changed something:]
    typedef typename mpl::if_<
          is_same< t_,T >
        , t_
        , boost::incomplete<t_>
        >::type type;

};

template <typename Variant>
struct quoted_enable_recursive
{
    template <typename T>
    struct apply
        : enable_recursive<T, Variant>
    {
    };
};

}} // namespace detail::variant
} // namespace boost

#endif // BOOST_MPL_VARIANT_DETAIL_ENABLE_RECURSIVE_STUB_HPP
