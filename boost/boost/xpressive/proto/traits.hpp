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
        // is_expr
        template<typename T>
        struct is_expr
          : mpl::false_
        {};

        template<typename Tag, typename Args, long Arity>
        struct is_expr<basic_expr<Tag, Args, Arity> >
          : mpl::true_
        {};

        template<typename Expr>
        struct is_expr<ref<Expr> >
          : mpl::true_
        {};

        // as_expr
        template<typename T, bool IsExpr>
        struct as_expr
        {
            typedef basic_expr<terminal_tag, mpl::vector1<typename call_traits<T>::value_type> > type;
        };

        template<typename T>
        struct as_expr<T, true>
        {
            typedef ref<T> type;
        };

        template<typename T>
        struct as_expr<ref<T>, true>
        {
            typedef ref<T> type;
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
    op::make_terminal const make_terminal = {};
    op::arg const arg = {};
    op::left const left = {};
    op::right const right = {};

    ///////////////////////////////////////////////////////////////////////////////
    // make_expr (unary)
    template<typename Tag, typename Arg>
    basic_expr<Tag, mpl::vector1<Arg> > const
    make_expr(Arg const &arg)
    {
        basic_expr<Tag, mpl::vector1<Arg> > that = {arg};
        return that;
    }

    template<typename Tag, typename Arg>
    basic_expr<Tag, mpl::vector1<ref<Arg> > > const
    make_expr(reference_wrapper<Arg> const &arg)
    {
        basic_expr<Tag, mpl::vector1<ref<Arg> > > that = {{arg.get()}};
        return that;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // make_expr (binary)
    template<typename Tag, typename Left, typename Right>
    basic_expr<Tag, mpl::vector2<Left, Right> > const
    make_expr(Left const &left, Right const &right)
    {
        basic_expr<Tag, mpl::vector2<Left, Right> > that = {left, right};
        return that;
    }

    template<typename Tag, typename Left, typename Right>
    basic_expr<Tag, mpl::vector2<ref<Left>, Right> > const
    make_expr(reference_wrapper<Left> const &left, Right const &right)
    {
        basic_expr<Tag, mpl::vector2<ref<Left>, Right> > that = {{left.get()}, right};
        return that;
    }

    template<typename Tag, typename Left, typename Right>
    basic_expr<Tag, mpl::vector2<Left, ref<Right> > > const
    make_expr(Left const &left, reference_wrapper<Right> const &right)
    {
        basic_expr<Tag, mpl::vector2<Left, ref<Right> > > that = {left, {right.get()}};
        return that;
    }

    template<typename Tag, typename Left, typename Right>
    basic_expr<Tag, mpl::vector2<ref<Left>, ref<Right> > > const
    make_expr(reference_wrapper<Left> const &left, reference_wrapper<Right> const &right)
    {
        basic_expr<Tag, mpl::vector2<ref<Left>, ref<Right> > > that = {{left.get()}, {right.get()}};
        return that;
    }
}}

#endif
