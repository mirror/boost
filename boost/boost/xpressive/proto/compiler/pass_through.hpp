///////////////////////////////////////////////////////////////////////////////
/// \file pass_through.hpp
/// 
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

    #ifndef BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006
    #define BOOST_PROTO_COMPILER_PASS_THROUGH_HPP_EAN_04_23_2006

    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/enum.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/xpressive/proto/proto.hpp>
    #include <boost/xpressive/proto/traits.hpp>

    namespace boost { namespace proto
    {
        template<typename DomainTag>
        struct pass_through_compiler
        {
            template<typename Expr, typename State, typename Visitor, typename Tag, typename Arity>
            struct apply_impl;

        #define BOOST_PROTO_DEFINE_META_COMPILE(z, n, data)\
            typename meta::compile<typename meta::arg_c<Expr, n>::type, State, Visitor, DomainTag>::type

        #define BOOST_PROTO_DEFINE_COMPILE(z, n, data)\
            proto::compile(proto::arg_c<n>(expr), state, visitor, DomainTag())

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/compiler/pass_through.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_DEFINE_COMPILE
        #undef BOOST_PROTO_DEFINE_META_COMPILE

            template<typename Expr, typename State, typename Visitor>
            struct apply_impl<Expr, State, Visitor, terminal_tag, mpl::long_<1> >
            {
                typedef Expr type;

                static type const &call(Expr const &expr, State const &, Visitor &)
                {
                    return expr;
                }
            };

            template<typename Expr, typename State, typename Visitor>
            struct apply
              : apply_impl<Expr, State, Visitor, typename Expr::tag_type, typename Expr::arity>
            {};

            template<typename Expr, typename State, typename Visitor>
            static typename apply<Expr, State, Visitor>::type
            call(Expr const &expr, State const &state, Visitor &visitor)
            {
                return apply<Expr, State, Visitor>::call(expr, state, visitor);
            }
        };

    }}

    #endif

#else

    #define N BOOST_PP_ITERATION()

            template<typename Expr, typename State, typename Visitor, typename Tag>
            struct apply_impl<Expr, State, Visitor, Tag, mpl::long_<N> >
            {
                typedef basic_expr<
                    Tag
                  , BOOST_PP_CAT(mpl::vector, N)<
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_META_COMPILE, ~)
                    >
                > type;

                static type call(Expr const &expr, State const &state, Visitor &visitor)
                {
                    type that = {
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_COMPILE, ~)
                    };
                    return that;
                }
            };

    #undef N

#endif
