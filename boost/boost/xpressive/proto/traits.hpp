///////////////////////////////////////////////////////////////////////////////
/// \file traits.hpp
/// Contains definitions for arg\<\>, arg_c\<\>, left\<\>,
/// right\<\>, tag\<\>, and the helper functions arg(), arg_c(),
/// left() and right().
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING
    #ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
    #define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

    #include <boost/ref.hpp>
    #include <boost/mpl/if.hpp>
    #include <boost/mpl/or.hpp>
    #include <boost/mpl/bool.hpp>
    #include <boost/call_traits.hpp>
    #include <boost/static_assert.hpp>
    #include <boost/utility/result_of.hpp>
    #include <boost/xpressive/proto/proto_fwd.hpp>
    #include <boost/xpressive/proto/ref.hpp>
    #include <boost/xpressive/proto/args.hpp>
    #include <boost/xpressive/proto/tags.hpp>
    #include <boost/xpressive/proto/transform/pass_through.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/arithmetic/sub.hpp>

    namespace boost { namespace proto
    {

        namespace meta
        {
            // is_ref
            template<typename T, typename EnableIf>
            struct is_ref
              : mpl::false_
            {};

            template<typename T>
            struct is_ref<T, typename T::is_boost_proto_ref_>
              : mpl::true_
            {};

            // is_expr
            template<typename T, typename EnableIf>
            struct is_expr
              : mpl::false_
            {};

            template<typename T>
            struct is_expr<T, typename T::is_boost_proto_expr_>
              : mpl::true_
            {};

            // as_expr
            template<typename T, typename EnableIf>
            struct as_expr
            {
                typedef expr<proto::tag::terminal, args1<typename call_traits<T>::value_type> > type;
            };

            template<typename T>
            struct as_expr<T, typename T::is_boost_proto_expr_>
            {
                typedef T type;
            };

            // as_expr_ref
            template<typename T, typename EnableIf>
            struct as_expr_ref
            {
                typedef expr<proto::tag::terminal, args1<T const &> > type;
            };

            template<typename T>
            struct as_expr_ref<T, typename T::is_boost_proto_expr_>
            {
                typedef ref<T> type;
            };

            template<typename Expr, typename N>
            struct arg
              : arg_c<Expr, N::value>
            {};

            // left
            template<typename Expr>
            struct left
            {
                typedef typename Expr::arg0_type::type type;
            };

            // right
            template<typename Expr>
            struct right
            {
                typedef typename Expr::arg1_type::type type;
            };

            // terminal
            template<typename T>
            struct terminal : has_identity_transform
            {
                terminal();
                typedef expr<proto::tag::terminal, args1<T> > type;
            };

            // unary_expr
            template<typename Tag, typename T>
            struct unary_expr : has_pass_through_transform<unary_expr<Tag, T> >
            {
                unary_expr();
                typedef expr<Tag, args1<T> > type;
            };

            // binary_expr
            template<typename Tag, typename T, typename U>
            struct binary_expr : has_pass_through_transform<binary_expr<Tag, T, U> >
            {
                binary_expr();
                typedef expr<Tag, args2<T, U> > type;
            };

        #define BOOST_PROTO_UNARY_GENERATOR(Name)\
            template<typename T>\
            struct Name : has_pass_through_transform<Name<T> >\
            {\
                Name();\
                typedef expr<proto::tag::Name, args1<T> > type;\
            };\
            /**/

        #define BOOST_PROTO_BINARY_GENERATOR(Name)\
            template<typename T, typename U>\
            struct Name : has_pass_through_transform<Name<T, U> >\
            {\
                Name();\
                typedef expr<proto::tag::Name, args2<T, U> > type;\
            };\
            /**/

            BOOST_PROTO_UNARY_GENERATOR(unary_plus)
            BOOST_PROTO_UNARY_GENERATOR(unary_minus)
            BOOST_PROTO_UNARY_GENERATOR(unary_star)
            BOOST_PROTO_UNARY_GENERATOR(complement)
            BOOST_PROTO_UNARY_GENERATOR(address_of)
            BOOST_PROTO_UNARY_GENERATOR(logical_not)
            BOOST_PROTO_UNARY_GENERATOR(pre_inc)
            BOOST_PROTO_UNARY_GENERATOR(pre_dec)
            BOOST_PROTO_UNARY_GENERATOR(post_inc)
            BOOST_PROTO_UNARY_GENERATOR(post_dec)

            BOOST_PROTO_BINARY_GENERATOR(left_shift)
            BOOST_PROTO_BINARY_GENERATOR(right_shift)
            BOOST_PROTO_BINARY_GENERATOR(multiply)
            BOOST_PROTO_BINARY_GENERATOR(divide)
            BOOST_PROTO_BINARY_GENERATOR(modulus)
            BOOST_PROTO_BINARY_GENERATOR(add)
            BOOST_PROTO_BINARY_GENERATOR(subtract)
            BOOST_PROTO_BINARY_GENERATOR(less)
            BOOST_PROTO_BINARY_GENERATOR(greater)
            BOOST_PROTO_BINARY_GENERATOR(less_equal)
            BOOST_PROTO_BINARY_GENERATOR(greater_equal)
            BOOST_PROTO_BINARY_GENERATOR(equal)
            BOOST_PROTO_BINARY_GENERATOR(not_equal)
            BOOST_PROTO_BINARY_GENERATOR(logical_or)
            BOOST_PROTO_BINARY_GENERATOR(logical_and)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_and)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_or)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_xor)
            BOOST_PROTO_BINARY_GENERATOR(comma)
            BOOST_PROTO_BINARY_GENERATOR(mem_ptr)

            BOOST_PROTO_BINARY_GENERATOR(assign)
            BOOST_PROTO_BINARY_GENERATOR(left_shift_assign)
            BOOST_PROTO_BINARY_GENERATOR(right_shift_assign)
            BOOST_PROTO_BINARY_GENERATOR(multiply_assign)
            BOOST_PROTO_BINARY_GENERATOR(divide_assign)
            BOOST_PROTO_BINARY_GENERATOR(modulus_assign)
            BOOST_PROTO_BINARY_GENERATOR(add_assign)
            BOOST_PROTO_BINARY_GENERATOR(subtract_assign)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_and_assign)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_or_assign)
            BOOST_PROTO_BINARY_GENERATOR(bitwise_xor_assign)
            BOOST_PROTO_BINARY_GENERATOR(subscript)

        #undef BOOST_PROTO_UNARY_GENERATOR
        #undef BOOST_PROTO_BINARY_GENERATOR

            // tag
            template<typename Expr>
            struct tag
            {
                typedef typename Expr::tag_type type;
            };

            // id
            template<typename Expr>
            struct id
              : deep_copy<Expr>
            {};

        #define BOOST_PROTO_ARG_N_TYPE(z, n, data)\
            typename proto::meta::unref<\
                typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, n), _type)\
            >::reference\
            /**/

        #define BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PROTO_MAX_ARITY, <boost/xpressive/proto/traits.hpp>))
        #include BOOST_PP_ITERATE()
        #undef BOOST_PP_ITERATION_PARAMS_1

        #undef BOOST_PROTO_ARG_N_TYPE
        }

        namespace op
        {
            struct as_expr
            {
                template<typename Sig>
                struct result;

                template<typename This, typename T>
                struct result<This(T)>
                  : meta::as_expr<typename meta::value_type<T>::type>
                {};

                template<typename T>
                ref<T> const &operator()(ref<T> const &t) const
                {
                    return t;
                }

                template<typename T>
                typename mpl::if_<
                    meta::is_expr<T>
                  , typename meta::as_expr<T>::type const &
                  , typename meta::as_expr<T>::type
                >::type
                operator()(T const &t) const
                {
                    return as_expr::call(t, meta::is_expr<T>());
                }

            private:
                template<typename T>
                static typename meta::as_expr<T>::type const &call(T const &t, mpl::true_)
                {
                    return t;
                }

                template<typename T>
                static typename meta::as_expr<T>::type call(T const &t, mpl::false_)
                {
                    typename meta::as_expr<T>::type that = {t};
                    return that;
                }
            };

            struct as_expr_ref
            {
                template<typename Sig>
                struct result;

                template<typename This, typename T>
                struct result<This(T)>
                  : meta::as_expr_ref<typename meta::value_type<T>::type>
                {};

                template<typename T>
                ref<T> const &operator()(ref<T> const &t) const
                {
                    return t;
                }

                template<typename T>
                typename meta::as_expr_ref<T>::type
                operator()(T const &t) const
                {
                    typename meta::as_expr_ref<T>::type that = {t};
                    return that;
                }
            };

            struct make_terminal
            {
                template<typename Sig>
                struct result;

                template<typename This, typename T>
                struct result<This(T)>
                  : meta::terminal<typename meta::value_type<T>::type>
                {};

                template<typename T>
                typename meta::terminal<T>::type operator()(T const &t) const
                {
                    typename meta::terminal<T>::type that = {t};
                    return that;
                }
            };

            template<long N>
            struct arg_c
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : meta::arg_c<typename meta::value_type<Expr>::type, N>
                {};

                template<typename Expr>
                typename meta::arg_c<Expr, N>::type const &operator()(Expr const &expr) const
                {
                    return meta::arg_c<Expr, N>::call(expr);
                }
            };

            template<typename N>
            struct arg
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : meta::arg<typename meta::value_type<Expr>::type, N>
                {};

                template<typename Expr>
                typename meta::arg<Expr, N>::type const &operator()(Expr const &expr) const
                {
                    return meta::arg<Expr, N>::call(expr);
                }
            };

            struct left
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : meta::left<typename meta::value_type<Expr>::type>
                {};

                template<typename Expr>
                typename meta::left<Expr>::type const &operator()(Expr const &expr) const
                {
                    return proto::unref(expr.cast().arg0);
                }
            };

            struct right
            {
                template<typename Sig>
                struct result;

                template<typename This, typename Expr>
                struct result<This(Expr)>
                  : meta::right<typename meta::value_type<Expr>::type>
                {};

                template<typename Expr>
                typename meta::right<Expr>::type const &operator()(Expr const &expr) const
                {
                    return proto::unref(expr.cast().arg1);
                }
            };

        }

        op::as_expr const as_expr = {};
        op::as_expr_ref const as_expr_ref = {};
        op::make_terminal const make_terminal = {};
        op::left const left = {};
        op::right const right = {};

        template<typename Expr>
        typename meta::unref<typename Expr::type::arg0_type>::reference
        arg(Expr const &expr)
        {
            return proto::unref(expr.cast().arg0);
        };

        template<typename N, typename Expr>
        typename meta::arg<Expr, N>::reference arg(Expr const &expr)
        {
            return meta::arg<Expr, N>::call(expr);
        };

        template<long N, typename Expr>
        typename meta::arg_c<Expr, N>::reference arg_c(Expr const &expr)
        {
            return meta::arg_c<Expr, N>::call(expr);
        };

    }}

    #endif

#else // PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

        #if N > 0
            template<BOOST_PP_ENUM_PARAMS(N, typename A)>
            struct function<
                BOOST_PP_ENUM_PARAMS(N, A)
                BOOST_PP_ENUM_TRAILING_PARAMS(BOOST_PP_SUB(BOOST_PROTO_MAX_ARITY, N), void BOOST_PP_INTERCEPT), void
            > : has_identity_transform
            {
                typedef expr<proto::tag::function, BOOST_PP_CAT(args, N)<BOOST_PP_ENUM_PARAMS(N, A)> > type;
            };

            template<typename Expr, typename Fun>
            struct eval<Expr, Fun, N>
              : boost::result_of<Fun(typename Expr::tag_type BOOST_PP_ENUM_TRAILING(N, BOOST_PROTO_ARG_N_TYPE, ~))>
            {};
        #endif

        #if N == 0
            // If N == 0, this could be a terminal, which must be handled differently
            template<typename Expr>
            struct arg_c<Expr, 0>
              : unref<typename Expr::arg0_type>
            {
                static typename unref<typename Expr::arg0_type>::reference call(Expr const &expr)
                {
                    return proto::unref(expr.cast().BOOST_PP_CAT(arg, N));
                }
            };
        #else
            template<typename Expr>
            struct arg_c<Expr, N>
            {
                typedef typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, N), _type)::type type;
                typedef type const &reference;

                static type const &call(Expr const &expr)
                {
                    return expr.cast().BOOST_PP_CAT(arg, N).cast();
                }
            };
        #endif

    #undef N

#endif
