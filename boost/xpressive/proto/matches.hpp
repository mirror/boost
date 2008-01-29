#ifndef BOOST_PP_IS_ITERATING
    ///////////////////////////////////////////////////////////////////////////////
    /// \file matches.hpp
    /// Contains definition of matches\<\> metafunction for determining if
    /// a given expression matches a given pattern.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #ifndef BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006
    #define BOOST_PROTO_MATCHES_HPP_EAN_11_03_2006

    #include <boost/xpressive/proto/detail/prefix.hpp> // must be first include
    #include <boost/detail/workaround.hpp>
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
    #include <boost/mpl/logical.hpp>
    #include <boost/mpl/apply.hpp>
    #include <boost/mpl/aux_/template_arity.hpp>
    #include <boost/mpl/aux_/lambda_arity_param.hpp>
    #include <boost/utility/enable_if.hpp>
    #include <boost/type_traits/is_convertible.hpp>
    #include <boost/type_traits/is_reference.hpp>
    #include <boost/type_traits/is_pointer.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/traits.hpp>
    #include <boost/xpressive/proto/transform/when.hpp>
    #include <boost/xpressive/proto/detail/suffix.hpp> // must be last include

    // Some compilers (like GCC) need extra help figuring out a template's arity.
    // I use MPL's BOOST_MPL_AUX_LAMBDA_ARITY_PARAM() macro to disambiguate, which
    // which is controlled by the BOOST_MPL_LIMIT_METAFUNCTION_ARITY macro. If
    // You define BOOST_PROTO_MAX_ARITY to be greater than
    // BOOST_MPL_LIMIT_METAFUNCTION_ARITY on these compilers, things don't work.
    // You must define BOOST_MPL_LIMIT_METAFUNCTION_ARITY to be greater.
    #ifdef BOOST_MPL_CFG_EXTENDED_TEMPLATE_PARAMETERS_MATCHING
    # if BOOST_PROTO_MAX_ARITY > BOOST_MPL_LIMIT_METAFUNCTION_ARITY
    #  error BOOST_MPL_LIMIT_METAFUNCTION_ARITY must be at least as large as BOOST_PROTO_MAX_ARITY
    # endif
    #endif

    #if defined(_MSC_VER) && (_MSC_VER >= 1020)
    # pragma warning(push)
    # pragma warning(disable:4305) // 'specialization' : truncation from 'const int' to 'bool'
    #endif

    namespace boost { namespace proto
    {

        namespace detail
        {
            struct ignore;

            template<typename Expr, typename Grammar>
            struct matches_;

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

            template<typename T, typename U>
            struct array_matches
              : mpl::false_
            {};

            template<typename T, std::size_t M>
            struct array_matches<T[M], T *>
              : mpl::true_
            {};

            template<typename T, std::size_t M>
            struct array_matches<T[M], T const *>
              : mpl::true_
            {};

            template<typename T, std::size_t M>
            struct array_matches<T[M], T[proto::N]>
              : mpl::true_
            {};

            template<typename T, typename U
                BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(long Arity = mpl::aux::template_arity<U>::value)
            >
            struct lambda_matches
              : mpl::false_
            {};

            template<typename T>
            struct lambda_matches<T, proto::_ BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(-1)>
              : mpl::true_
            {};

            template<typename T>
            struct lambda_matches<T, T BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(-1)>
              : mpl::true_
            {};

            template<typename T, std::size_t M, typename U>
            struct lambda_matches<T[M], U BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(-1)>
              : array_matches<T[M], U>
            {};

            template<typename T, std::size_t M>
            struct lambda_matches<T[M], T[M] BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(-1)>
              : mpl::true_
            {};

            template<template<typename> class T, typename Expr0, typename Grammar0>
            struct lambda_matches<T<Expr0>, T<Grammar0> BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(1) >
              : lambda_matches<Expr0, Grammar0>
            {};

            // vararg_matches_impl
            template<typename Args1, typename Back, long From, long To>
            struct vararg_matches_impl;

            // vararg_matches
            template<typename Args1, typename Args2, typename Back, bool Can, bool Zero, typename EnableIf = void>
            struct vararg_matches
              : mpl::false_
            {};

            template<typename Args1, typename Args2, typename Back>
            struct vararg_matches<Args1, Args2, Back, true, true, typename Back::proto_is_vararg_>
              : matches_<proto::expr<ignore, Args1, Args1::size>, proto::expr<ignore, Args2, Args1::size> >
            {};

            template<typename Args1, typename Args2, typename Back>
            struct vararg_matches<Args1, Args2, Back, true, false, typename Back::proto_is_vararg_>
              : and2<
                    matches_<proto::expr<ignore, Args1, Args2::size>, proto::expr<ignore, Args2, Args2::size> >::value
                  , vararg_matches_impl<Args1, typename Back::proto_base_expr, Args2::size + 1, Args1::size>
                >
            {};

            // How terminal_matches<> handles references and cv-qualifiers.
            // The cv and ref_ matter *only* if the grammar has a top-level ref_.
            //
            // Expr     |   Grammar  |  Match
            // ------------------------------
            // T            T           yes
            // T &          T           yes
            // T const &    T           yes
            // T            T &         no
            // T &          T &         yes
            // T const &    T &         no
            // T            T const &   no
            // T &          T const &   no
            // T const &    T const &   yes

            template<typename T, typename U>
            struct is_cv_ref_compatible
              : mpl::true_
            {};

            template<typename T, typename U>
            struct is_cv_ref_compatible<T, U &>
              : mpl::false_
            {};

            template<typename T, typename U>
            struct is_cv_ref_compatible<T &, U &>
              : mpl::bool_<is_const<T>::value == is_const<U>::value>
            {};

        #if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
            // MSVC-7.1 has lots of problems with array types that have been
            // deduced. Partially specializing terminal_matches<> on array types
            // doesn't seem to work.
            template<
                typename T
              , typename U
              , bool B = is_array<BOOST_PROTO_UNCVREF(T)>::value
            >
            struct terminal_array_matches
              : mpl::false_
            {};

            template<typename T, typename U, std::size_t M>
            struct terminal_array_matches<T, U(&)[M], true>
              : is_convertible<T, U(&)[M]>
            {};

            template<typename T, typename U>
            struct terminal_array_matches<T, U(&)[proto::N], true>
              : is_convertible<T, U *>
            {};

            template<typename T, typename U>
            struct terminal_array_matches<T, U *, true>
              : is_convertible<T, U *>
            {};

            // terminal_matches
            template<typename T, typename U>
            struct terminal_matches
              : mpl::or_<
                    mpl::and_<
                        is_cv_ref_compatible<T, U>
                      , lambda_matches<
                            BOOST_PROTO_UNCVREF(T)
                          , BOOST_PROTO_UNCVREF(U)
                        >
                    >
                  , terminal_array_matches<T, U>
                >
            {};
        #else
            // terminal_matches
            template<typename T, typename U>
            struct terminal_matches
              : mpl::and_<
                    is_cv_ref_compatible<T, U>
                  , lambda_matches<
                        BOOST_PROTO_UNCVREF(T)
                      , BOOST_PROTO_UNCVREF(U)
                    >
                >
            {};

            template<typename T, std::size_t M>
            struct terminal_matches<T(&)[M], T(&)[proto::N]>
              : mpl::true_
            {};

            template<typename T, std::size_t M>
            struct terminal_matches<T(&)[M], T *>
              : mpl::true_
            {};
        #endif

            template<typename T>
            struct terminal_matches<T, T>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T &, T>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T const &, T>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T, proto::_>
              : mpl::true_
            {};

            template<typename T>
            struct terminal_matches<T, exact<T> >
              : mpl::true_
            {};

            template<typename T, typename U>
            struct terminal_matches<T, proto::convertible_to<U> >
              : is_convertible<T, U>
            {};

            // matches_
            template<typename Expr, typename Grammar>
            struct matches_
              : mpl::false_
            {};

            template<typename Expr>
            struct matches_< Expr, proto::_ >
              : mpl::true_
            {};

            template<typename Tag, typename Args1, long N1, typename Args2, long N2>
            struct matches_< proto::expr<Tag, Args1, N1>, proto::expr<Tag, Args2, N2> >
              : vararg_matches< Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
            {};

            template<typename Tag, typename Args1, long N1, typename Args2, long N2>
            struct matches_< proto::expr<Tag, Args1, N1>, proto::expr<proto::_, Args2, N2> >
              : vararg_matches< Args1, Args2, typename Args2::back_, (N1+2 > N2), (N2 > N1) >
            {};

            template<typename Args1, typename Args2, long N2>
            struct matches_< proto::expr<tag::terminal, Args1, 0>, proto::expr<proto::_, Args2, N2> >
              : mpl::false_
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_< proto::expr<Tag, Args1, 1>, proto::expr<Tag, Args2, 1> >
              : matches_<typename Args1::arg0::proto_base_expr, typename Args2::arg0::proto_base_expr>
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_< proto::expr<Tag, Args1, 1>, proto::expr<proto::_, Args2, 1> >
              : matches_<typename Args1::arg0::proto_base_expr, typename Args2::arg0::proto_base_expr>
            {};

            template<typename Args1, typename Args2>
            struct matches_< proto::expr<tag::terminal, Args1, 0>, proto::expr<tag::terminal, Args2, 0> >
              : terminal_matches<typename Args1::arg0, typename Args2::arg0>
            {};

        #define BOOST_PROTO_MATCHES_N_FUN(z, n, data)\
            matches_<\
                typename Args1::BOOST_PP_CAT(arg, n)::proto_base_expr\
              , typename Args2::BOOST_PP_CAT(arg, n)::proto_base_expr\
            >

        #define BOOST_PROTO_DEFINE_MATCHES(z, n, data)\
            matches_<\
                typename Expr::proto_base_expr\
              , typename BOOST_PP_CAT(G, n)::proto_base_expr\
            >

        #define BOOST_PROTO_DEFINE_LAMBDA_MATCHES(z, n, data)\
            lambda_matches<\
                BOOST_PP_CAT(Expr, n)\
              , BOOST_PP_CAT(Grammar, n)\
            >

        #if BOOST_PROTO_MAX_LOGICAL_ARITY > BOOST_PROTO_MAX_ARITY
            #define BOOST_PP_ITERATION_PARAMS_1 (4, (2, BOOST_PROTO_MAX_LOGICAL_ARITY, <boost/xpressive/proto/matches.hpp>, 1))
        #else
            #define BOOST_PP_ITERATION_PARAMS_1 (4, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/matches.hpp>, 1))
        #endif
        #include BOOST_PP_ITERATE()

        #define BOOST_PP_ITERATION_PARAMS_1 (4, (2, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/matches.hpp>, 2))
        #include BOOST_PP_ITERATE()

        #undef BOOST_PROTO_MATCHES_N_FUN
        #undef BOOST_PROTO_DEFINE_MATCHES
        #undef BOOST_PROTO_DEFINE_LAMBDA_MATCHES

            // handle proto::if_
            template<typename Expr, typename If, typename Then, typename Else>
            struct matches_<Expr, proto::if_<If, Then, Else> >
              : mpl::eval_if<
                    typename when<_, If>::template result<void(Expr, mpl::void_, mpl::void_)>::type
                  , matches_<Expr, typename Then::proto_base_expr>
                  , matches_<Expr, typename Else::proto_base_expr>
                >::type
            {};

            template<typename Expr, typename If>
            struct matches_<Expr, proto::if_<If> >
              : when<_, If>::template result<void(Expr, mpl::void_, mpl::void_)>::type
            {};

            // handle proto::not_
            template<typename Expr, typename Grammar>
            struct matches_<Expr, not_<Grammar> >
              : mpl::not_<matches_<Expr, typename Grammar::proto_base_expr> >
            {};

            // handle proto::switch_
            template<typename Expr, typename Cases>
            struct matches_<Expr, switch_<Cases> >
              : matches_<
                    Expr
                  , typename Cases::template case_<typename Expr::proto_tag>::proto_base_expr
                >
            {};
        }

        namespace result_of
        {
            template<typename Expr, typename Grammar>
            struct matches
              : detail::matches_<typename Expr::proto_base_expr, typename Grammar::proto_base_expr>
            {};
        }

        namespace wildcardns_
        {
            struct _ : proto::callable
            {
                typedef _ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef Expr type;
                };

                template<typename Expr, typename State, typename Visitor>
                Expr const &operator ()(Expr const &expr, State const &, Visitor &) const
                {
                    return expr;
                }
            };
        }

        namespace control
        {
            // not_
            template<typename Grammar>
            struct not_ : proto::callable
            {
                typedef not_ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef Expr type;
                };

                template<typename Expr, typename State, typename Visitor>
                Expr const &operator ()(Expr const &expr, State const &, Visitor &) const
                {
                    return expr;
                }
            };

            // if_
            template<typename If, typename Then, typename Else>
            struct if_ : proto::callable
            {
                typedef if_ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef
                        typename mpl::if_<
                            typename when<_, If>::template result<void(Expr, State, Visitor)>::type
                          , when<_, Then>
                          , when<_, Else>
                        >::type
                    branch;

                    typedef typename branch::template result<void(Expr, State, Visitor)>::type type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef
                        typename mpl::if_<
                            typename when<_, If>::template result<void(Expr, State, Visitor)>::type
                          , when<_, Then>
                          , when<_, Else>
                        >::type
                    branch;

                    return branch()(expr, state, visitor);
                }
            };

            // or_
            template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G)>
            struct or_ : proto::callable
            {
                typedef or_ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef typename detail::matches_<Expr, or_>::which which;
                    typedef typename which::template result<void(Expr, State, Visitor)>::type type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef typename detail::matches_<Expr, or_>::which which;
                    return which()(expr, state, visitor);
                }
            };

            // and_
            template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G)>
            struct and_ : proto::callable
            {
                typedef and_ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef typename detail::last<and_>::type which;
                    typedef typename which::template result<void(Expr, State, Visitor)>::type type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef typename detail::last<and_>::type which;
                    return which()(expr, state, visitor);
                }
            };

            // switch_
            template<typename Cases>
            struct switch_ : proto::callable
            {
                typedef switch_ proto_base_expr;

                template<typename Sig> struct result {};

                template<typename This, typename Expr, typename State, typename Visitor>
                struct result<This(Expr, State, Visitor)>
                {
                    typedef typename Cases::template case_<typename Expr::proto_tag> impl;
                    typedef typename impl::template result<void(Expr, State, Visitor)>::type type;
                };

                template<typename Expr, typename State, typename Visitor>
                typename result<void(Expr, State, Visitor)>::type
                operator ()(Expr const &expr, State const &state, Visitor &visitor) const
                {
                    typedef typename Cases::template case_<typename Expr::proto_tag> impl;
                    return impl()(expr, state, visitor);
                }
            };

            template<typename T>
            struct exact
            {};

            template<typename T>
            struct convertible_to
            {};

            template<typename Grammar>
            struct vararg
              : Grammar
            {
                typedef void proto_is_vararg_;
            };
        }

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G)>
        struct is_callable<or_<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, G)> >
          : mpl::true_
        {};

        template<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, typename G)>
        struct is_callable<and_<BOOST_PP_ENUM_PARAMS(BOOST_PROTO_MAX_LOGICAL_ARITY, G)> >
          : mpl::true_
        {};

        template<typename Grammar>
        struct is_callable<not_<Grammar> >
          : mpl::true_
        {};

        template<typename If, typename Then, typename Else>
        struct is_callable<if_<If, Then, Else> >
          : mpl::true_
        {};

        template<typename Grammar>
        struct is_callable<vararg<Grammar> >
          : mpl::true_
        {};

    }}

    #if defined(_MSC_VER) && (_MSC_VER >= 1020)
    # pragma warning(pop)
    #endif

    #endif

#elif BOOST_PP_ITERATION_FLAGS() == 1

    #define N BOOST_PP_ITERATION()

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

        #if N <= BOOST_PROTO_MAX_LOGICAL_ARITY
            template<BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct last<proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
            {
                typedef BOOST_PP_CAT(G, BOOST_PP_DEC(N)) type;
            };

            template<bool B, typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct BOOST_PP_CAT(or, N)
              : BOOST_PP_CAT(or, BOOST_PP_DEC(N))<
                    matches_<Expr, typename G1::proto_base_expr>::value
                  , Expr, BOOST_PP_ENUM_SHIFTED_PARAMS(N, G)
                >
            {};

            template<typename Expr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
            struct BOOST_PP_CAT(or, N)<true, Expr, BOOST_PP_ENUM_PARAMS(N, G)>
              : mpl::true_
            {
                typedef G0 which;
            };

            // handle proto::or_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_<Expr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : BOOST_PP_CAT(or, N)<
                    matches_<typename Expr::proto_base_expr, typename G0::proto_base_expr>::value,
                    typename Expr::proto_base_expr, BOOST_PP_ENUM_PARAMS(N, G)
                >
            {};

            // handle proto::and_
            template<typename Expr, BOOST_PP_ENUM_PARAMS(N, typename G)>
            struct matches_<Expr, proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
              : detail::BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_DEFINE_MATCHES(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_MATCHES, ~)
                >
            {};
        #endif

    #undef N

#elif BOOST_PP_ITERATION_FLAGS() == 2

    #define N BOOST_PP_ITERATION()

            template<typename Args, typename Back, long To>
            struct vararg_matches_impl<Args, Back, N, To>
              : and2<
                    matches_<typename Args::BOOST_PP_CAT(arg, BOOST_PP_DEC(N))::proto_base_expr, Back>::value
                  , vararg_matches_impl<Args, Back, N + 1, To>
                >
            {};

            template<typename Args, typename Back>
            struct vararg_matches_impl<Args, Back, N, N>
              : matches_<typename Args::BOOST_PP_CAT(arg, BOOST_PP_DEC(N))::proto_base_expr, Back>
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
            struct matches_< proto::expr<Tag, Args1, N>, proto::expr<Tag, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
                >
            {};

            template<typename Tag, typename Args1, typename Args2>
            struct matches_< proto::expr<Tag, Args1, N>, proto::expr<proto::_, Args2, N> >
              : BOOST_PP_CAT(and, N)<
                    BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                    BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
                >
            {};

    #undef N

#endif

