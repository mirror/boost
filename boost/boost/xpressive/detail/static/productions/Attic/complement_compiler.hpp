////////////////////////////////////////////////////////////////////////////
// complement_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_COMPLEMENT_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_COMPLEMENT_COMPILER_HPP_EAN_10_04_2005

#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/transform.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/utility/never_true.hpp>
#include <boost/xpressive/detail/static/productions/set_compilers.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>
#include <boost/xpressive/detail/static/productions/charset_transforms.hpp>

namespace boost { namespace xpressive { namespace detail
{

    template<typename OpTag, typename Arg0, typename Arg1>
    struct complement
    {
        // If your compile breaks here, then you are applying the complement operator ~
        // to something that does not support it. For instance, ~(_ >> 'a') will trigger this
        // assertion because the sub-expression (_ >> 'a') has no complement.
        BOOST_MPL_ASSERT((never_true<OpTag>));
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Char, bool Not>
    struct complement<proto::terminal_tag, literal_placeholder<Char, Not>, void>
    {
        template<typename Expr, typename>
        struct apply
          : proto::meta::terminal<literal_placeholder<Char, !Not> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {{proto::arg(expr).ch_}};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Traits, int Size>
    struct complement<proto::terminal_tag, set_matcher<Traits, Size>, void>
    {
        template<typename Expr, typename>
        struct apply
          : proto::meta::terminal<set_matcher<Traits, Size> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.complement();
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement<proto::terminal_tag, posix_charset_placeholder, void>
    {
        template<typename, typename>
        struct apply
          : proto::meta::terminal<posix_charset_placeholder>
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.not_ = !that.arg0.not_;
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Right>
    struct complement<proto::subscript_tag, set_initializer_type, Right>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : charset_transform::BOOST_NESTED_TEMPLATE apply<
                Expr
              , dont_care
              , Visitor
            >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &visitor)
        {
            return charset_transform::call(expr, dont_care(), visitor, true);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // for complementing a list-initialized set, as in ~(set= 'a','b','c')
    template<typename Left, typename Right>
    struct complement<proto::comma_tag, Left, Right>
    {
        // First, convert the parse tree into a set_matcher
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::terminal<typename proto::compiler<proto::comma_tag, lst_tag>
                ::BOOST_NESTED_TEMPLATE apply<
                    Expr
                  , dont_care
                  , Visitor
                >::type
            >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &visitor)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::compile(expr, dont_care(), visitor, lst_tag())};
            that.arg0.complement();
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Arg>
    struct complement<lookahead_tag<true>, Arg, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::unary_expr<lookahead_tag<false>, Arg>
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::arg(expr)};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Arg>
    struct complement<lookbehind_tag<true>, Arg, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::unary_expr<lookbehind_tag<false>, Arg>
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::arg(expr)};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement<proto::terminal_tag, assert_word_placeholder<word_boundary<true> >, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::terminal<assert_word_placeholder<word_boundary<false> > >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement<proto::terminal_tag, logical_newline_placeholder, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::right_shift<
                typename proto::meta::unary_expr<lookahead_tag<false>, Expr>::type
              , proto::meta::terminal<any_matcher>::type
            >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {{expr}, {any_matcher()}};
            return that;
       }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complementing a complement is a no-op
    template<typename Arg>
    struct complement<proto::complement_tag, Arg, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
        {
            typedef Arg type;
        };

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            return proto::arg(expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Char>
    struct complement<proto::terminal_tag, range_placeholder<Char>, void>
    {
        template<typename Expr, typename Visitor>
        struct apply
          : proto::meta::terminal<range_placeholder<Char> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Expr, Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Expr, Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.not_ = !that.arg0.not_;
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complement_transform
    struct complement_transform
    {
        template<typename Expr, typename, typename Visitor>
        struct apply
        {
            typedef typename Expr::arg0_type expr_type;
            typedef typename expr_type::tag_type tag_type;
            typedef typename proto::meta::unref<typename expr_type::arg0_type>::type arg0_type;
            typedef typename proto::meta::unref<typename expr_type::arg1_type>::type arg1_type;

            typedef complement<tag_type, arg0_type, arg1_type> complement;
            typedef typename complement::BOOST_NESTED_TEMPLATE apply<expr_type, Visitor>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &visitor)
        {
            typedef typename apply<Expr, State, Visitor>::complement complement;
            return complement::call(proto::arg(expr), visitor);
        }
    };

}}}

namespace boost { namespace proto
{

    template<>
    struct compiler<complement_tag, xpressive::detail::seq_tag, void>
      : transform_compiler<xpressive::detail::complement_transform, xpressive::detail::seq_tag>
    {
    };

}}

#endif
