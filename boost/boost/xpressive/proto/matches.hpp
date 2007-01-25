#ifndef BOOST_PP_IS_ITERATING
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

    #include <boost/xpressive/proto/detail/prefix.hpp>

    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_shifted.hpp>
    #include <boost/preprocessor/repetition/enum_shifted_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
    #include <boost/config.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/and.hpp>
    #include <boost/mpl/bool.hpp>
    #include <boost/mpl/apply.hpp>
    #include <boost/mpl/placeholders.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/type_traits/add_const.hpp>
    #include <boost/type_traits/add_reference.hpp>
    #include <boost/type_traits/is_convertible.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>

    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace detail
        {
            template<typename Expr>
            struct deref;

            template<typename Expr, typename Grammar>
            struct matches_impl;

            // and_ and or_ implementation
            template<bool B, typename Expr, typename G0>
            struct or1
              : mpl::bool_<B>
            {
                typedef G0 grammar;
            };

            template<bool B>
            struct and1
              : mpl::bool_<B>
            {};

            template<typename And>
            struct last;

            template<typename T>
            struct wrap_terminal
            {
                wrap_terminal(typename add_reference<typename add_const<T>::type>::type);
            };

            // terminal_matches
            template<typename Expr, typename Grammar>
            struct terminal_matches
              : is_convertible<Expr, wrap_terminal<Grammar> >
            {};

            template<typename Expr>
            struct terminal_matches<Expr, mpl::_>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T, exact<T> >
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

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, 1>, expr<mpl::_, Args2, 1> >
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

            template<typename Args1, typename Args2>
            struct matches_impl< expr<tag::terminal, Args1, 1>, expr<mpl::_, Args2, 1> >
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

        #undef BOOST_PROTO_MATCHES_N_FUN
        #undef BOOST_PROTO_DEFINE_MATCHES
        #undef BOOST_PROTO_DEFINE_TERMINAL_MATCHES

            // handle proto::if_
            template<typename Expr, typename Pred>
            struct matches_impl<Expr, if_<Pred> >
              : mpl::apply1<Pred, Expr>::type
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
                typedef typename detail::matches_impl<Expr, or_>::grammar grammar_type;
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

            template<typename Expr, typename State, typename Visitor>
            struct apply
            {
                typedef typename detail::last<and_>::type grammar_type;
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

        template<typename T>
        struct exact
        {};
    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            template<BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct last<proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
            {
                typedef BOOST_PP_CAT(G, BOOST_PP_DEC(N)) type;
            };

            template<bool B, typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct BOOST_PP_CAT(or, N)
              : BOOST_PP_CAT(or, BOOST_PP_DEC(N))<
                    matches_impl<Expr, typename deref<G1>::type>::value
                  , Expr 
                    BOOST_PP_COMMA_IF(BOOST_PP_DEC(N)) BOOST_PP_ENUM_SHIFTED_PARAMS(N, G)
                >
            {};

            template<typename Expr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
            struct BOOST_PP_CAT(or, N)<true, Expr, BOOST_PP_ENUM_PARAMS(N, G)>
              : mpl::true_
            {
                typedef G0 grammar;
            };

            template<bool B, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
            struct BOOST_PP_CAT(and, N)
              : BOOST_PP_CAT(and, BOOST_PP_DEC(N))<
                    P0::value BOOST_PP_COMMA_IF(BOOST_PP_SUB(N,2))
                    BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_DEC(N), P)
                >
            {};

            template<BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), typename P)>
            struct BOOST_PP_CAT(and, N)<false, BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(N), P)>
              : mpl::false_
            {};

            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Expr)
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)
            >
            struct terminal_matches<T<BOOST_PP_ENUM_PARAMS(N, Expr)>, T<BOOST_PP_ENUM_PARAMS(N, Grammar)> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_DEFINE_TERMINAL_MATCHES(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_TERMINAL_MATCHES, ~)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, N>, expr<Tag, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, N)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, N)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, N>, expr<mpl::_, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, N)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, N)
                >
            {};

            // handle proto::or_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_impl<Expr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : BOOST_PP_CAT(or, N)<
                    matches_impl<typename Expr::type, typename deref<G0>::type>::value,
                    typename Expr::type, BOOST_PP_ENUM_PARAMS(N, G)
                >
            {};

            // handle proto::and_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_impl<Expr, proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : detail::BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_DEFINE_MATCHES(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_MATCHES, ~)
                >
            {};

    #undef N

#endif

