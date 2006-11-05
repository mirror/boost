///////////////////////////////////////////////////////////////////////////////
/// \file matches.hpp
/// Contains definition of matches\<\> metafunction for determining if
/// a given expression matches a given pattern.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006
#define BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006

#include <boost/config.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost { namespace proto
{

    namespace detail
    {
        // and_
        template<bool B, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
        struct and_impl
        {
            typedef typename and_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>::type type;
            BOOST_STATIC_CONSTANT(bool, value = type::value);
        };

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename P)>
        struct and_impl<false, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
        {
            typedef mpl::false_ type;
            BOOST_STATIC_CONSTANT(bool, value = false);
        };

        template<>
        struct and_impl<true>
        {
            typedef mpl::true_ type;
            BOOST_STATIC_CONSTANT(bool, value = true);
        };

        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
        struct and_
          : and_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
        {};

        // or_
        template<bool B, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
        struct or_impl
        {
            typedef typename or_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>::type type;
            BOOST_STATIC_CONSTANT(bool, value = type::value);
        };

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename P)>
        struct or_impl<true, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
        {
            typedef mpl::true_ type;
            BOOST_STATIC_CONSTANT(bool, value = true);
        };

        template<>
        struct or_impl<false>
        {
            typedef mpl::false_ type;
            BOOST_STATIC_CONSTANT(bool, value = false);
        };

        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
        struct or_
          : or_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
        {};

        // terminal_matches
        template<typename Expr, typename Grammar>
        struct terminal_matches
          : mpl::false_
        {};

        template<typename Grammar>
        struct terminal_matches<Grammar, Grammar>
          : mpl::true_
        {};

        template<typename Expr>
        struct terminal_matches<Expr, mpl::_>
          : mpl::true_
        {};

        template<template<typename> class T, typename Expr0, typename Grammar0>
        struct terminal_matches<T<Expr0>, T<Grammar0> >
          : terminal_matches<Expr0, Grammar0>
        {};

        template<template<typename, typename> class T, typename Expr0, typename Expr1, typename Grammar0, typename Grammar1>
        struct terminal_matches<T<Expr0, Expr1>, T<Grammar0, Grammar1> >
          : and_<
                terminal_matches<Expr0, Grammar0>
              , terminal_matches<Expr1, Grammar1>
            >
        {};

        template<template<typename, typename, typename> class T, typename Expr0, typename Expr1, typename Expr2, typename Grammar0, typename Grammar1, typename Grammar2>
        struct terminal_matches<T<Expr0, Expr1, Expr2>, T<Grammar0, Grammar1, Grammar2> >
          : and_<
                terminal_matches<Expr0, Grammar0>
              , terminal_matches<Expr1, Grammar1>
              , terminal_matches<Expr2, Grammar2>
            >
        {};

        template<template<typename, typename, typename, typename> class T, typename Expr0, typename Expr1, typename Expr2, typename Expr3, typename Grammar0, typename Grammar1, typename Grammar2, typename Grammar3>
        struct terminal_matches<T<Expr0, Expr1, Expr2, Expr3>, T<Grammar0, Grammar1, Grammar2, Grammar3> >
          : and_<
                terminal_matches<Expr0, Grammar0>
              , terminal_matches<Expr1, Grammar1>
              , terminal_matches<Expr2, Grammar2>
              , terminal_matches<Expr3, Grammar3>
            >
        {};

        // matches_impl
    #define BOOST_PROTO_MATCHES_N_FUN2(z, n, data)\
        matches<\
            typename meta::arg_c< basic_expr<Tag, Args1, data>, n >::type\
          , typename meta::arg_c< basic_expr<Tag, Args2, data>, n >::type\
        >\
        /**/

        template<typename Expr, typename Grammar>
        struct matches_impl;

        template<typename Expr>
        struct matches_impl< Expr, mpl::_ >
          : mpl::true_
        {};

        template<typename Tag1, typename Args1, long Arity1, typename Tag2, typename Args2, long Arity2>
        struct matches_impl< basic_expr<Tag1, Args1, Arity1>, basic_expr<Tag2, Args2, Arity2> >
          : mpl::false_
        {};

        template<typename Tag, typename Args1, typename Args2>
        struct matches_impl< basic_expr<Tag, Args1, 1>, basic_expr<Tag, Args2, 1> >
          : BOOST_PROTO_MATCHES_N_FUN2(1, 0, 1)
        {};

        template<typename Args1, typename Args2>
        struct matches_impl< basic_expr<terminal_tag, Args1, 1>, basic_expr<terminal_tag, Args2, 1> >
          : terminal_matches<
                typename meta::arg< basic_expr<terminal_tag, Args1, 1> >::type
              , typename meta::arg< basic_expr<terminal_tag, Args2, 1> >::type
            >
        {};

    #define BOOST_PROTO_EXPR_CHECK2(z, n, data)\
        template<typename Tag, typename Args1, typename Args2>\
        struct matches_impl< basic_expr<Tag, Args1, n>, basic_expr<Tag, Args2, n> >\
          : and_<BOOST_PP_ENUM_ ## z(n, BOOST_PROTO_MATCHES_N_FUN2, n) >\
        {};\
        /**/

        BOOST_PP_REPEAT_FROM_TO(2, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_EXPR_CHECK2, ~)

    #undef BOOST_PROTO_EXPR_CHECK2
    #undef BOOST_PROTO_MATCHES_N_FUN2

        // by default, assume parameter is an expression generator ... 
        // (this also works for extends_tag<> types because they are also generators)
        template<typename Expr>
        struct deref
        {
            typedef typename Expr::type type;
        };

        // ... but it could be a plain expression ...
        template<typename Tag, typename Args, long Arity>
        struct deref<basic_expr<Tag, Args, Arity> >
        {
            typedef basic_expr<Tag, Args, Arity> type;
        };

        // ... or the placeholder
        template<>
        struct deref<mpl::_>
        {
            typedef mpl::_ type;
        };
    }

    template<typename Expr, typename Grammar>
    struct matches
      : mpl::or_<
            is_same<Expr, typename detail::deref<Grammar>::type>
          , detail::matches_impl<Expr, typename detail::deref<Grammar>::type>
        >
    {};

    template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
    struct or_
    {
        typedef or_ type;
    };

#define BOOST_PROTO_DEFINE_MATCHES(z, n, data)\
    matches< Expr, BOOST_PP_CAT(G, n) >

#define BOOST_PROTO_DEFINE_OR(z, n, data)\
    template<typename Expr, BOOST_PP_ENUM_PARAMS_Z(z, n, typename G)>\
    struct matches<Expr, or_<BOOST_PP_ENUM_PARAMS_Z(z, n, G)> >\
      : detail::or_< BOOST_PP_ENUM_ ## z(n, BOOST_PROTO_DEFINE_MATCHES, ~) >\
    {};\
    /**/

    BOOST_PP_REPEAT_FROM_TO(2, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_OR, ~)

#undef BOOST_PROTO_DEFINE_MATCHES
#undef BOOST_PROTO_DEFINE_OR

    template<typename Pred>
    struct if_
    {
        typedef if_ type;
    };

    template<typename Expr, typename Pred>
    struct matches<Expr, if_<Pred> >
      : mpl::apply1<Pred, Expr>
    {};

}}

#endif

