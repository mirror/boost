///////////////////////////////////////////////////////////////////////////////
/// \file expr.hpp
/// Contains definition of expr\<\> class template.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING
    #ifndef BOOST_PROTO_EXPR_HPP_EAN_04_01_2005
    #define BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

    #include <boost/preprocessor/inc.hpp>
    #include <boost/preprocessor/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/preprocessor/punctuation/comma.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/repetition/repeat_from_to.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/args.hpp>
    #include <boost/xpressive/proto/traits.hpp>

    namespace boost { namespace proto
    {
    #define BOOST_PROTO_ARG(z, n, data)\
        typedef typename Args::BOOST_PP_CAT(arg, n) BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);\
        BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type) BOOST_PP_CAT(arg, n);\
        /**/

    #define BOOST_PROTO_VOID(z, n, data)\
        typedef void BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type);\
        /**/

    #define BOOST_PROTO_AS_OP(z, n, data)\
        proto::as_expr_ref(BOOST_PP_CAT(a,n))\
        /**/

    #define BOOST_PP_ITERATION_PARAMS_1 (4, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/expr.hpp>, 1))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_1

    #undef BOOST_PROTO_ARG
    #undef BOOST_PROTO_VOID
    #undef BOOST_PROTO_AS_OP
    }}

    #if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))
    namespace boost
    {
        template<typename T>
        struct result_of;

    #define BOOST_PP_ITERATION_PARAMS_1 (4, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/expr.hpp>, 2))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_1
    }

    #endif

    #endif // BOOST_PROTO_EXPR_HPP_EAN_04_01_2005

#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() < 2

        template<typename Tag, typename Args>
        struct expr<Tag, Args, BOOST_PP_ITERATION() >
        {
            typedef Tag tag_type;
            typedef expr expr_type;
            typedef Args args_type;
            typedef mpl::long_<BOOST_PP_ITERATION()> arity;
            typedef proto_expr_tag fusion_tag;
            typedef void is_boost_proto_expr_;

            BOOST_PP_REPEAT(BOOST_PP_ITERATION(), BOOST_PROTO_ARG, _)
            BOOST_PP_REPEAT_FROM_TO(BOOST_PP_ITERATION(), BOOST_PROTO_MAX_ARITY, BOOST_PROTO_VOID, _)

            expr const &cast() const
            {
                return *this;
            }

            template<typename A>
            expr<tag::assign, args2<ref<expr>, typename meta::as_expr_ref<A>::type> > const
            operator =(A const &a) const
            {
                expr<tag::assign, args2<ref<expr>, typename meta::as_expr_ref<A>::type> > that = {{*this}, proto::as_expr_ref(a)};
                return that;
            }

            template<typename A>
            expr<tag::subscript, args2<ref<expr>, typename meta::as_expr_ref<A>::type> > const
            operator [](A const &a) const
            {
                expr<tag::subscript, args2<ref<expr>, typename meta::as_expr_ref<A>::type> > that = {{*this}, proto::as_expr_ref(a)};
                return that;
            }

            template<typename Sig>
            struct result;

            template<typename This>
            struct result<This()>
            {
                typedef expr<tag::function, args1<ref<expr> > > type;
            };

            expr<tag::function, args1<ref<expr> > > const
            operator ()() const
            {
                expr<tag::function, args1<ref<expr> > > that = {{*this}};
                return that;
            }

    #define BOOST_PP_ITERATION_PARAMS_2 (3, (1, BOOST_PP_DEC(BOOST_PROTO_MAX_ARITY), <boost/xpressive/proto/expr.hpp>))
    #include BOOST_PP_ITERATE()
    #undef BOOST_PP_ITERATION_PARAMS_2
        };

#elif BOOST_PP_ITERATION_DEPTH() == 2

    #define N BOOST_PP_ITERATION()

        template<typename This BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct result<This(BOOST_PP_ENUM_PARAMS(N, A))>
        {
            typedef expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<expr> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> > type;
        };

        template<BOOST_PP_ENUM_PARAMS(N, typename A)>
        expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<expr> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> > const
        operator ()(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const &a)) const
        {
            expr<tag::function, BOOST_PP_CAT(args, BOOST_PP_INC(N))<ref<expr> BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(N, typename meta::as_expr_ref<A, >::type BOOST_PP_INTERCEPT)> > that = {{*this} BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_AS_OP, _)};
            return that;
        }

    #undef N

#elif BOOST_PP_ITERATION_DEPTH() == 1 && BOOST_PP_ITERATION_FLAGS() == 2

    #define N BOOST_PP_ITERATION()

        template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct result_of<proto::expr<Tag, Args, Arity>(BOOST_PP_ENUM_PARAMS(N, A))>
          : proto::expr<Tag, Args, Arity>::BOOST_NESTED_TEMPLATE result<void(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

        template<typename Tag, typename Args, long Arity BOOST_PP_ENUM_TRAILING_PARAMS(N, typename A)>
        struct result_of<proto::expr<Tag, Args, Arity> const(BOOST_PP_ENUM_PARAMS(N, A))>
          : proto::expr<Tag, Args, Arity>::BOOST_NESTED_TEMPLATE result<void(BOOST_PP_ENUM_PARAMS(N, A))>
        {};

    #undef N

#endif
