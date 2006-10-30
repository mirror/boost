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
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/ref.hpp>

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

        // is_expr
        template<typename T>
        struct is_expr
          : mpl::or_<is_basic_expr<T>, is_ref<T> >
        {};

        // as_expr
        template<typename T>
        struct as_expr<T, false>
        {
            typedef basic_expr<terminal_tag, mpl::vector1<typename call_traits<T>::value_type> > type;
        };

        template<typename T>
        struct as_expr<T, true>
        {
            typedef T type;
        };

        // as_expr_ref
        template<typename T>
        struct as_expr_ref<T, false, false>
        {
            typedef basic_expr<terminal_tag, mpl::vector1<typename call_traits<T>::value_type> > type;
        };

        template<typename T>
        struct as_expr_ref<T, true, false>
        {
            typedef ref<typename remove_cv<T>::type> type;
        };

        template<typename T>
        struct as_expr_ref<T, false, true>
        {
            BOOST_STATIC_ASSERT(!is_ref<typename T::expr_type>::value);
            typedef T type;
        };

        // arg
        template<typename Expr>
        struct arg
        {
            BOOST_STATIC_ASSERT(1 == Expr::arity::value);
            typedef typename Expr::arg0_type type;
        };

        // left
        template<typename Expr>
        struct left
        {
            BOOST_STATIC_ASSERT(2 == Expr::arity::value);
            typedef typename Expr::arg0_type type;
        };

        // right
        template<typename Expr>
        struct right
        {
            BOOST_STATIC_ASSERT(2 == Expr::arity::value);
            typedef typename Expr::arg1_type type;
        };

        // terminal
        template<typename T>
        struct terminal
        {
            typedef typename call_traits<T>::value_type value_type;
            typedef basic_expr<terminal_tag, mpl::vector1<value_type> > type;
        };

        // unary_expr
        template<typename Tag, typename T>
        struct unary_expr
        {
            typedef basic_expr<Tag, mpl::vector1<T> > type;
        };

        // binary_expr
        template<typename Tag, typename T, typename U>
        struct binary_expr
        {
            typedef basic_expr<Tag, mpl::vector2<T, U> > type;
        };

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
            typename meta::as_expr<T>::type operator()(T const &t) const
            {
                typename meta::as_expr<T>::type that = {t};
                return that;
            }

            template<typename Tag, typename Args, long Arity>
            basic_expr<Tag, Args, Arity> const &operator()(basic_expr<Tag, Args, Arity> const &t) const
            {
                return t;
            }

            template<typename T>
            ref<T> const &operator()(ref<T> const &t) const
            {
                return t;
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
            typename meta::as_expr_ref<T>::type operator()(T const &t) const
            {
                typename meta::as_expr_ref<T>::type that = {t};
                return that;
            }

            template<typename T>
            ref<T> const &operator()(ref<T> const &t) const
            {
                return t;
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

        struct arg
        {
            template<typename Sig>
            struct result;

            template<typename This, typename Expr>
            struct result<This(Expr)>
              : meta::arg<typename meta::value_type<Expr>::type>
            {};

            template<typename Expr>
            typename Expr::arg0_type const &operator()(Expr const &expr) const
            {
                return expr.cast().arg0;
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
            typename Expr::arg0_type const &operator()(Expr const &expr) const
            {
                return expr.cast().arg0;
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
            typename Expr::arg1_type const &operator()(Expr const &expr) const
            {
                return expr.cast().arg1;
            }
        };

    }

    op::as_expr const as_expr = {};
    op::as_expr_ref const as_expr_ref = {};
    op::make_terminal const make_terminal = {};
    op::arg const arg = {};
    op::left const left = {};
    op::right const right = {};
}}

#endif
