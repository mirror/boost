//-----------------------------------------------------------------------------
// boost variant/recursive_wrapper_fwd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Eric Friedman, Itay Maman
//
// Portions Copyright (C) 2002 David Abrahams
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_VARIANT_RECURSIVE_WRAPPER_FWD_HPP
#define BOOST_VARIANT_RECURSIVE_WRAPPER_FWD_HPP

#include "boost/config.hpp"
#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
#   include "boost/mpl/apply_if.hpp"
#   include "boost/mpl/bool.hpp"
#   include "boost/mpl/identity.hpp"
#   include "boost/type.hpp"
#   include "boost/type_traits/detail/bool_trait_def.hpp"
#endif

#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// class template recursive_wrapper
//
// Enables recursive types in templates by breaking cyclic dependencies.
//
// For example:
//
//   class my;
//
//   typedef variant< int, recursive_wrapper<my> > var;
//
//   class my {
//     var var_;
//     ...
//   };
//
template <typename T> class recursive_wrapper;

///////////////////////////////////////////////////////////////////////////////
// metafunction is_recursive_wrapper (modeled on code by David Abrahams)
//
// True iff specified type matches recursive_wrapper<T>.
//

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T>
struct is_recursive_wrapper
    : mpl::false_
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_recursive_wrapper,(T))
};

template <typename T>
struct is_recursive_wrapper< recursive_wrapper<T> >
    : mpl::true_
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,is_recursive_wrapper,(T))
};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace detail {

typedef char (&yes_recursive_wrapper_t)[1];
typedef char (&no_recursive_wrapper_t)[2];

no_recursive_wrapper_t is_recursive_wrapper_test(...);

template<typename T>
yes_recursive_wrapper_t is_recursive_wrapper_test(
      type< ::boost::recursive_wrapper<T> >
    );

template<typename T>
struct is_recursive_wrapper_impl
{
    BOOST_STATIC_CONSTANT(bool, value = (
          sizeof(is_recursive_wrapper_test(type<T>()))
          == sizeof(yes_recursive_wrapper_t)
        ));
};

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF1(
      is_recursive_wrapper
    , T
    , (::boost::detail::is_recursive_wrapper_impl<T>::value)
    )

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

///////////////////////////////////////////////////////////////////////////////
// metafunction unwrap_recursive
//
// If specified type T matches recursive_wrapper<U>, then U; else T.
//

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T>
struct unwrap_recursive
{
    typedef T type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,unwrap_recursive,(T))
};

template <typename T>
struct unwrap_recursive< recursive_wrapper<T> >
{
    typedef T type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(1,unwrap_recursive,(T))
};

#else // defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template <typename T>
struct unwrap_recursive
    : mpl::apply_if<
          is_recursive_wrapper<T>
        , T
        , mpl::identity< T >
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,unwrap_recursive,(T))
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION workaround

} // namespace boost

#endif // BOOST_VARIANT_RECURSIVE_WRAPPER_FWD_HPP
