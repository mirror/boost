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
    #include <boost/mpl/bool.hpp>
    #include <boost/mpl/apply.hpp>
    #include <boost/mpl/aux_/template_arity.hpp>
    #include <boost/mpl/aux_/lambda_arity_param.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/type_traits/is_convertible.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp>

    namespace boost { namespace proto
    {

        namespace detail
        {
            struct _;

            template<typename Expr, typename Grammar>
            struct matches_impl;

            // and_ and or_ implementation
            template<bool B, typename Expr, typename G0>
            struct or1
              : mpl::bool_<B>
            {
                typedef G0 which;
            };

            template<bool B>
            struct and1
              : mpl::bool_<B>
            {};

            template<bool B, typename Pred>
            struct and2;

            template<typename And>
            struct last;

            template<typename T, typename U
                BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(long Arity = mpl::aux::template_arity<U>::value)
            >
            struct lambda_matches
              : is_same<T, U>
            {};

            template<typename T>
            struct lambda_matches<T, proto::_ BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(-1)>
              : mpl::true_
            {};

            template<template<typename> class T, typename Expr0, typename Grammar0>
            struct lambda_matches<T<Expr0>, T<Grammar0> BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(1) >
              : lambda_matches<Expr0, Grammar0>
            {};

            // wrap_terminal
            template<typename T>
            struct wrap_terminal
            {
                wrap_terminal(T const &);
                
                template<typename U>
                wrap_terminal(U const &, typename enable_if<lambda_matches<U, T> >::type * = 0 );
            };

            template<typename T>
            struct wrap_terminal<T &>
            {
                wrap_terminal(T &);
                
                template<typename U>
                wrap_terminal(U &, typename enable_if<lambda_matches<U, T> >::type * = 0 );
            };

            template<typename T>
            struct wrap_terminal<T const &>
            {
                wrap_terminal(T const &);

                template<typename U>
                wrap_terminal(U const &, typename enable_if<lambda_matches<U, T> >::type * = 0 );
            };

            // vararg_matches_impl
            template<typename Args1, typename Back, long From, long To>
            struct vararg_matches_impl;

            // vararg_matches
            template<typename Args1, typename Args2, typename Back, bool Can, bool Zero, typename EnableIf = void>
            struct vararg_matches
              : mpl::false_
            {};

            template<typename Args1, typename Args2, typename Back>
            struct vararg_matches<Args1, Args2, Back, true, true, typename Back::boost_proto_is_vararg_>
              : matches_impl<expr<_, Args1, Args1::size>, expr<_, Args2, Args1::size> >
            {};

            template<typename Args1, typename Args2, typename Back>
            struct vararg_matches<Args1, Args2, Back, true, false, typename Back::boost_proto_is_vararg_>
              : and2<
                    matches_impl<expr<_, Args1, Args2::size>, expr<_, Args2, Args2::size> >::value
                  , vararg_matches_impl<Args1, typename Back::type, Args2::size + 1, Args1::size>
                >
            {};

            // terminal_matches
            template<typename Expr, typename Grammar>
            struct terminal_matches
              : is_convertible<Expr, wrap_terminal<Grammar> >
            {};

            template<typename Expr>
            struct terminal_matches<Expr, proto::_>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T, exact<T> >
              : mpl::true_
            {};

            template<typename T, std::size_t M, typename U>
            struct terminal_matches<T(&)[M], U(&)[proto::N]>
              : is_convertible<T(&)[M], U(&)[M]>
            {};

            // matches_impl
            template<typename Expr, typename Grammar>
            struct matches_impl
              : mpl::false_
            {};

            template<typename Expr>
            struct matches_impl< Expr, proto::_ >
              : mpl::true_
            {};

            template<typename Tag, typename Args1, long N1, typename Args2, long N2>
            struct matches_impl< expr<Tag, Args1, N1>, expr<Tag, Args2, N2> >
              : vararg_matches< Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
            {};

            template<typename Tag, typename Args1, long N1, typename Args2, long N2>
            struct matches_impl< expr<Tag, Args1, N1>, expr<proto::_, Args2, N2> >
              : vararg_matches< Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, 1>, expr<Tag, Args2, 1> >
              : matches_impl<typename Args1::arg0::type, typename Args2::arg0::type>
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, 1>, expr<proto::_, Args2, 1> >
              : matches_impl<typename Args1::arg0::type, typename Args2::arg0::type>
            {};

            template<typename Args1, typename Args2>
            struct matches_impl< expr<tag::terminal, Args1, 1>, expr<tag::terminal, Args2, 1> >
              : terminal_matches<typename Args1::arg0, typename Args2::arg0>
            {};

            template<typename Args1, typename Args2>
            struct matches_impl< expr<tag::terminal, Args1, 1>, expr<proto::_, Args2, 1> >
              : terminal_matches<typename Args1::arg0, typename Args2::arg0>
            {};

        #define BOOST_PROTO_MATCHES_N_FUN(z, n, data)\
            matches_impl<\
                typename Args1::BOOST_PP_CAT(arg, n)::type\
              , typename Args2::BOOST_PP_CAT(arg, n)::type\
            >

        #define BOOST_PROTO_DEFINE_MATCHES(z, n, data)\
            matches_impl<\
                typename Expr::type\
              , typename BOOST_PP_CAT(G, n)::type\
            >

        #define BOOST_PROTO_DEFINE_LAMBDA_MATCHES(z, n, data)\
            lambda_matches<\
                BOOST_PP_CAT(Expr, n)\
              , BOOST_PP_CAT(Grammar, n)\
            >

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/matches.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PROTO_MATCHES_N_FUN
        #undef BOOST_PROTO_DEFINE_MATCHES
        #undef BOOST_PROTO_DEFINE_LAMBDA_MATCHES

            // handle proto::if_
            template<typename Expr, typename Pred>
            struct matches_impl<Expr, if_<Pred> >
              : mpl::apply1<Pred, Expr>::type
            {};

        }

        template<typename Expr, typename Grammar>
        struct matches
          : detail::matches_impl<typename Expr::type, typename Grammar::type>
        {};

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
        struct or_
        {
            typedef or_ type;

            template<typename Expr, typename State, typename Visitor>
            struct apply
            {
                typedef typename detail::matches_impl<Expr, or_>::which which;
                typedef typename which::template apply<Expr, State, Visitor>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call(Expr const &expr, State const &state, Visitor &visitor)
            {
                typedef typename detail::matches_impl<Expr, or_>::which which;
                return which::call(expr, state, visitor);
            }
        };

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_ARITY, typename G)>
        struct and_
        {
            typedef and_ type;

            template<typename Expr, typename State, typename Visitor>
            struct apply
            {
                typedef typename detail::last<and_>::type which;
                typedef typename which::template apply<Expr, State, Visitor>::type type;
            };

            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call(Expr const &expr, State const &state, Visitor &visitor)
            {
                typedef typename detail::last<and_>::type which;
                return which::call(expr, state, visitor);
            }
        };

        struct _ : has_identity_transform
        {
            typedef _ type;
        };

        template<typename Pred>
        struct if_ : has_identity_transform
        {
            typedef if_ type;
        };

        template<typename Grammar>
        struct vararg
          : Grammar
        {
            typedef void boost_proto_is_vararg_;
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
                    matches_impl<Expr, typename G1::type>::value
                  , Expr, BOOST_PP_ENUM_SHIFTED_PARAMS(N, G)
                >
            {};

            template<typename Expr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
            struct BOOST_PP_CAT(or, N)<true, Expr, BOOST_PP_ENUM_PARAMS(N, G)>
              : mpl::true_
            {
                typedef G0 which;
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

            template<typename Args, typename Back, long To>
            struct vararg_matches_impl<Args, Back, N, To>
              : and2<
                    matches_impl<typename Args::BOOST_PP_CAT(arg, BOOST_PP_DEC(N))::type, Back>::value
                  , vararg_matches_impl<Args, Back, N + 1, To>
                >
            {};

            template<typename Args, typename Back>
            struct vararg_matches_impl<Args, Back, N, N>
              : matches_impl<typename Args::BOOST_PP_CAT(arg, BOOST_PP_DEC(N))::type, Back>
            {};

            template<
                template<BOOST_PP_ENUM_PARAMS(N, typename BOOST_PP_INTERCEPT)> class T
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Expr)
                BOOST_PP_ENUM_TRAILING_PARAMS(N, typename Grammar)
            >
            struct lambda_matches<T<BOOST_PP_ENUM_PARAMS(N, Expr)>, T<BOOST_PP_ENUM_PARAMS(N, Grammar)> BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(N) >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_DEFINE_LAMBDA_MATCHES(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_LAMBDA_MATCHES, ~)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, N>, expr<Tag, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_impl< expr<Tag, Args1, N>, expr<proto::_, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
                >
            {};

            // handle proto::or_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_impl<Expr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : BOOST_PP_CAT(or, N)<
                    matches_impl<typename Expr::type, typename G0::type>::value,
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

