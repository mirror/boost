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

    #include <boost/mpl/if.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/enum.hpp>
    #include <boost/preprocessor/iterate.hpp>
    #include <boost/xpressive/proto/proto.hpp>

    namespace boost { namespace proto
    {
        namespace meta
        {
            template<typename Expr, typename State, typename Visitor, typename DomainTag>
            struct is_same_expr
              : is_same<
                    typename meta::compile<typename Expr::type, State, Visitor, DomainTag>::type
                  , typename Expr::type
                >
            {};

            template<typename Expr, typename State, typename Visitor, typename DomainTag
                , bool IsSameExpr = is_same_expr<Expr, State, Visitor, DomainTag>::value
            >
            struct compile_if
            {
                typedef typename meta::compile<typename Expr::type, State, Visitor, DomainTag>::type type;

                static type call(Expr const &expr, State const &state, Visitor &visitor)
                {
                    return proto::compile(expr.cast(), state, visitor, DomainTag());
                }
            };

            template<typename Expr, typename State, typename Visitor, typename DomainTag>
            struct compile_if<Expr, State, Visitor, DomainTag, true>
            {
                typedef Expr type;

                static Expr const &call(Expr const &expr, State const &, Visitor &)
                {
                    return expr;
                }
            };
        }

        template<typename Expr, typename State, typename Visitor, typename DomainTag>
        typename meta::compile_if<Expr, State, Visitor, DomainTag>::type
        compile_if(Expr const &expr, State const &state, Visitor &visitor, DomainTag)
        {
            return meta::compile_if<Expr, State, Visitor, DomainTag>::call(expr, state, visitor);
        }

        template<typename DomainTag>
        struct pass_through_compiler
        {
            template<typename Expr, typename State, typename Visitor, typename Tag, typename Arity>
            struct apply_impl;

        #define BOOST_PROTO_DEFINE_META_COMPILE(z, n, data)\
            typename meta::compile_if<typename BOOST_PP_CAT(BOOST_PP_CAT(Expr::arg, n), _type), State, Visitor, DomainTag>::type

        #define BOOST_PROTO_DEFINE_COMPILE(z, n, data)\
            proto::compile_if(BOOST_PP_CAT(expr.arg, n), state, visitor, DomainTag())

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/compiler/pass_through.hpp>))

        #include BOOST_PP_ITERATE()

        #undef BOOST_PP_ITERATION_PARAMS_1
        #undef BOOST_PROTO_DEFINE_COMPILE
        #undef BOOST_PROTO_DEFINE_META_COMPILE

            template<typename Expr, typename State, typename Visitor>
            struct apply_impl<Expr, State, Visitor, tag::terminal, mpl::long_<1> >
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
                typedef expr<
                    Tag
                  , BOOST_PP_CAT(args, N)<
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_META_COMPILE, ~)
                    >
                > expr_type;

                typedef is_same<typename Expr::type, expr_type> is_same_expr;
                typedef typename mpl::if_<is_same_expr, Expr, expr_type>::type type;

                static type call(Expr const &expr, State const &state, Visitor &visitor)
                {
                    return apply_impl::call_(expr, state, visitor, is_same_expr());
                }

            private:
                static type call_(Expr const &expr, State const &state, Visitor &visitor, mpl::false_)
                {
                    type that = {
                        BOOST_PP_ENUM(N, BOOST_PROTO_DEFINE_COMPILE, ~)
                    };
                    return that;
                }

                static type const &call_(Expr const &expr, State const &, Visitor &, mpl::true_)
                {
                    return expr;
                }
            };

    #undef N

#endif
