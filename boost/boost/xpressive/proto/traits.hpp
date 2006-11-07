///////////////////////////////////////////////////////////////////////////////
/// \file traits.hpp
/// Contains definitions for arg_type\<\>, left_type\<\>,
/// right_type\<\>, tag_type\<\>, and the helper functions arg(), left(),
/// and right().
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005
#define BOOST_PROTO_ARG_TRAITS_HPP_EAN_04_01_2005

#include <boost/ref.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/call_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/ref.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace proto
{

    namespace meta
    {
        // is_basic_expr
        template<typename T>
        struct is_basic_expr
          : mpl::false_
        {};

        template<typename Tag, typename Args, long Arity>
        struct is_basic_expr<basic_expr<Tag, Args, Arity> >
          : mpl::true_
        {};

        template<typename T>
        struct is_basic_expr<T const>
          : is_basic_expr<T>
        {};

        // is_ref
        template<typename T>
        struct is_ref
          : mpl::false_
        {};

        template<typename T>
        struct is_ref<ref<T> >
          : mpl::true_
        {};

        template<typename T>
        struct is_ref<T const>
          : is_ref<T>
        {};

        template<typename T>
        struct is_extends<T const>
          : is_extends<T>
        {};

        // is_expr
        template<typename T>
        struct is_expr
          : mpl::or_<is_basic_expr<T>, is_ref<T>, is_extends<T> >
        {};

        // as_expr
        template<typename T>
        struct as_expr<T, false>
        {
            BOOST_STATIC_ASSERT(!is_reference<T>::value);
            typedef basic_expr<terminal_tag, mpl::vector1<typename call_traits<T>::value_type> > type;
        };

        template<typename T>
        struct as_expr<T, true>
          : mpl::if_<is_extends<T>, typename T::expr_type, T>
        {};

        // as_expr_ref
        template<typename T>
        struct as_expr_ref<T, false>
        {
            BOOST_STATIC_ASSERT(!is_reference<T>::value);
            typedef basic_expr<terminal_tag, mpl::vector1<typename call_traits<T>::value_type> > type;
        };

        template<typename T>
        struct as_expr_ref<T, true>
          : mpl::if_<is_ref<T>, T, ref<typename T::expr_type> >
        {};

        // arg, arg_c
    #define BOOST_PROTO_DEFINE_ARG_C(z, N, data)\
        template<typename Expr>\
        struct arg_c<Expr, N>\
        {\
            typedef typename unref<typename Expr::BOOST_PP_CAT(BOOST_PP_CAT(arg, N), _type)>::type type;\
            \
            static type const &call(Expr const &expr)\
            {\
                return proto::unref(expr.cast().BOOST_PP_CAT(arg, N));\
            }\
        };\
        /**/

        BOOST_PP_REPEAT(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_ARG_C, _)

    #undef BOOST_PROTO_DEFINE_ARG_C

        template<typename Expr, typename N>
        struct arg
          : arg_c<Expr, N::value>
        {};

        // left
        template<typename Expr>
        struct left
        {
            BOOST_STATIC_ASSERT(2 == Expr::expr_type::arity::value);
            typedef typename unref<typename Expr::arg0_type>::type type;
        };

        // right
        template<typename Expr>
        struct right
        {
            BOOST_STATIC_ASSERT(2 == Expr::expr_type::arity::value);
            typedef typename unref<typename Expr::arg1_type>::type type;
        };

        // terminal
        template<typename T>
        struct terminal
        {
            BOOST_STATIC_ASSERT(!is_reference<T>::value);
            typedef typename call_traits<T>::value_type value_type;
            typedef basic_expr<terminal_tag, mpl::vector1<value_type> > type;
        };

        // unary_expr
        template<typename Tag, typename T>
        struct unary_expr
        {
            BOOST_STATIC_ASSERT(!is_reference<T>::value);
            typedef basic_expr<Tag, mpl::vector1<T> > type;
        };

        // binary_expr
        template<typename Tag, typename T, typename U>
        struct binary_expr
        {
            BOOST_STATIC_ASSERT(!is_reference<T>::value);
            BOOST_STATIC_ASSERT(!is_reference<U>::value);
            typedef basic_expr<Tag, mpl::vector2<T, U> > type;
        };

    #define BOOST_PROTO_UNARY_GENERATOR(Name)\
        template<typename T>\
        struct Name\
        {\
            typedef basic_expr<BOOST_PP_CAT(Name, _tag), mpl::vector1<T> > type;\
        };\
        /**/

    #define BOOST_PROTO_BINARY_GENERATOR(Name)\
        template<typename T, typename U>\
        struct Name\
        {\
            typedef basic_expr<BOOST_PP_CAT(Name, _tag), mpl::vector2<T, U> > type;\
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

        // function
    #define BOOST_PROTO_DEFINE_FUNCTION(z, n, data)\
        template<BOOST_PP_ENUM_PARAMS_Z(z, n, typename A)>\
        struct function<BOOST_PP_ENUM_PARAMS_Z(z, n, A)>\
        {\
            typedef basic_expr<function_tag, BOOST_PP_CAT(mpl::vector, n)<BOOST_PP_ENUM_PARAMS_Z(z, n, A)> > type;\
        };\
        /**/

        BOOST_PP_REPEAT_FROM_TO(1, BOOST_PROTO_MAX_ARITY, BOOST_PROTO_DEFINE_FUNCTION, _)

    #undef BOOST_PROTO_DEFINE_FUNCTION

        // tag
        template<typename Expr>
        struct tag
        {
            typedef typename Expr::tag_type type;
        };
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
                return t.cast();
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
                return as_expr_ref::call(t, meta::is_expr<T>());
            }
           
        private:
            template<typename T>
            static typename meta::as_expr_ref<T>::type call(T const &t, mpl::true_)
            {
                ref<typename T::expr_type> that = {t.cast()};
                return that;
            }

            template<typename T>
            static typename meta::as_expr_ref<T>::type call(T const &t, mpl::false_)
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
    typename meta::unref<typename Expr::expr_type::arg0_type>::type const &
    arg(Expr const &expr)
    {
        return proto::unref(expr.cast().arg0);
    };

    template<typename N, typename Expr>
    typename meta::arg<Expr, N>::type const &arg(Expr const &expr)
    {
        return meta::arg<Expr, N>::call(expr);
    };

    template<long N, typename Expr>
    typename meta::arg_c<Expr, N>::type const &arg_c(Expr const &expr)
    {
        return meta::arg_c<Expr, N>::call(expr);
    };

}}

#endif
