///////////////////////////////////////////////////////////////////////////////
/// \file matches.hpp
/// Contains definition of matches\<\> metafunction for determining if
/// a given expression matches a given pattern.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

    #ifndef BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006
    #define BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006

    #include <boost/config.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/and.hpp>
    #include <boost/mpl/bool.hpp>
    #include <boost/mpl/apply.hpp>
    #include <boost/mpl/placeholders.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>

    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

    namespace boost { namespace proto
    {

        namespace detail
        {
            template<typename Expr>
            struct deref;

            template<typename Expr, typename Grammar>
            struct matches_impl;

            // and_
            template<bool B, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), typename P, void)>
            struct and_impl
              : and_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), P)>
            {};

            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), typename P)>
            struct and_impl<false, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), P)>
              : mpl::false_
            {};

            template<>
            struct and_impl<true>
              : mpl::true_
            {};

            template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
            struct and_
              : and_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
            {};

            // or_
            template<bool B, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), typename P, void)>
            struct or_impl
              : or_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), P)>
            {};

            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), typename P)>
            struct or_impl<true, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), P)>
              : mpl::true_
            {};

            template<>
            struct or_impl<false>
              : mpl::false_
            {};

            template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename P, void)>
            struct or_
              : or_impl<P0::type::value, BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, P)>
            {};

            // which
            template<typename Expr, bool B, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename G, void)>
            struct which_impl
              : which_impl<
                    Expr
                  , matches_impl<Expr, typename deref<G1>::type>::type::value
                  , BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PROTO_MAX_ARITY, G)
                >
            {};

            template<typename Expr, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
            struct which_impl<Expr, true, BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, G)>
            {
                typedef G0 type;
            };

            template<typename Expr, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_ARITY, typename G, void)>
            struct which
              : which_impl<
                    typename Expr::type
                  , matches_impl<typename Expr::type, typename deref<G0>::type>::type::value
                  , BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, G)
                >
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

            // by default, assume parameter is an expression generator ...
            // (this also works for expr<>, ref<> and extends<> types because
            // they are also expression generators)
            template<typename Expr>
            struct deref
            {
                typedef typename Expr::type type;
            };

            // ... or the placeholder
            template<>
            struct deref<mpl::_>
            {
                typedef mpl::_ type;
            };

            // matches_impl
            template<typename Expr, typename Grammar>
            struct matches_impl
              : mpl::false_
            {};

            template<typename Expr>
            struct matches_impl< Expr, mpl::_ >
              : mpl::true_
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, 1>, expr<Tag, Args2, 1> >
              : matches_impl<
                    typename Args1::arg0::type
                  , typename deref<typename Args2::arg0>::type
                >
            {};

            template<typename Args1, typename Args2>
            struct matches_impl< expr<tag::terminal, Args1, 1>, expr<tag::terminal, Args2, 1> >
              : terminal_matches<
                    typename Args1::arg0
                  , typename Args2::arg0
                >
            {};

        #define BOOST_PROTO_MATCHES_N_FUN(z, n, data)\
            matches_impl<\
                typename Args1::BOOST_PP_CAT(arg, n)::type\
              , typename deref<typename Args2::BOOST_PP_CAT(arg, n)>::type\
            >

        #define BOOST_PROTO_DEFINE_MATCHES(z, n, data)\
            matches_impl<\
                typename Expr::type\
              , typename deref<BOOST_PP_CAT(G, n)>::type\
            >

        #define BOOST_PROTO_DEFINE_TERMINAL_MATCHES(z, n, data)\
            terminal_matches<\
                BOOST_PP_CAT(Expr, n)\
              , BOOST_PP_CAT(Grammar, n)\
            >

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/matches.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_MATCHES_N_FUN
        #undef BOOST_PROTO_DEFINE_MATCHES
        #undef BOOST_PROTO_DEFINE_TERMINAL_MATCHES

            // handle proto::if_
            template<typename Expr, typename Pred>
            struct matches_impl<Expr, if_<Pred> >
              : mpl::apply1<Pred, Expr>
            {};

        }

        template<typename Expr, typename Grammar>
        struct matches
          : detail::matches_impl<typename Expr::type, typename detail::deref<Grammar>::type>
        {};

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
        struct or_
        {
            typedef or_ type;

            template<typename Expr, typename State, typename Visitor>
            struct apply
            {
                typedef typename detail::which<
                    Expr
                  , BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, G)
                >::type grammar_type;

                typedef typename grammar_type::template apply<Expr, State, Visitor>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call(Expr const &expr, State const &state, Visitor &visitor)
            {
                typedef typename apply<Expr, State, Visitor>::grammar_type grammar_type;
                return grammar_type::call(expr, state, visitor);
            }
        };

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
        struct and_
        {
            typedef and_ type;
        };

        template<typename Pred>
        struct if_
        {
            typedef if_ type;
        };

        template<typename Expr, typename Grammar, typename Return>
        struct if_matches
          : enable_if<matches<Expr, Grammar>, Return>
        {};

        template<typename Expr, typename Grammar, typename Return>
        struct if_not_matches
          : disable_if<matches<Expr, Grammar>, Return>
        {};
    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Expr)
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)
            >
            struct terminal_matches<T<BOOST_PP_ENUM_PARAMS(N, Expr)>, T<BOOST_PP_ENUM_PARAMS(N, Grammar)> >
              : detail::and_<
                    BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_TERMINAL_MATCHES, ~)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, N>, expr<Tag, Args2, N> >
              : detail::and_<BOOST_PP_ENUM(N, BOOST_PROTO_MATCHES_N_FUN, N) >
            {};

            // handle proto::or_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_impl<Expr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : detail::or_< BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_MATCHES, ~) >
            {};

            // handle proto::and_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_impl<Expr, proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : detail::and_< BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_MATCHES, ~) >
            {};

    #undef N

#endif

