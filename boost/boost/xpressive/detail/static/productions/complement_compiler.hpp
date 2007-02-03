////////////////////////////////////////////////////////////////////////////
// complement_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_COMPLEMENT_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_COMPLEMENT_COMPILER_HPP_EAN_10_04_2005

#include <boost/mpl/not.hpp>
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

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Term>
    struct complement_terminal
    {
        // If your compile breaks here, then you are applying the complement operator ~
        // to something that does not support it. For instance, ~(_ >> 'a') will trigger this
        // assertion because the sub-expression (_ >> 'a') has no complement.
        BOOST_MPL_ASSERT((never_true<Term>));
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Char, typename Not>
    struct complement_terminal<literal_placeholder<Char, Not> >
    {
        template<typename>
        struct apply
          : proto::terminal<literal_placeholder<Char, typename mpl::not_<Not>::type> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {{proto::arg(expr).ch_}};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Traits, int Size>
    struct complement_terminal<set_matcher<Traits, Size> >
    {
        template<typename>
        struct apply
          : proto::terminal<set_matcher<Traits, Size> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.complement();
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement_terminal<posix_charset_placeholder>
    {
        template<typename>
        struct apply
          : proto::terminal<posix_charset_placeholder>
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.not_ = !that.arg0.not_;
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Char>
    struct complement_terminal<range_placeholder<Char> >
    {
        template<typename Visitor>
        struct apply
          : proto::terminal<range_placeholder<Char> >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::arg(expr)};
            that.arg0.not_ = !that.arg0.not_;
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement_terminal<assert_word_placeholder<word_boundary<true> > >
    {
        template<typename>
        struct apply
          : proto::terminal<assert_word_placeholder<word_boundary<false> > >
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<>
    struct complement_terminal<logical_newline_placeholder>
    {
        // ~_ln matches any one character that is not in the "newline" character class
        template<typename>
        struct apply
          : proto::terminal<posix_charset_placeholder>
        {};

        template<typename Expr, typename Visitor>
        static typename apply<Visitor>::type call(Expr const &, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {{"newline", true}};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Expr, typename Tag = typename Expr::tag_type>
    struct complement
    {
        // If your compile breaks here, then you are applying the complement operator ~
        // to something that does not support it. For instance, ~(_ >> 'a') will trigger this
        // assertion because the sub-expression (_ >> 'a') has no complement.
        BOOST_MPL_ASSERT((never_true<Tag>));
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Expr>
    struct complement<Expr, proto::tag::terminal>
      : complement_terminal<typename proto::result_of::arg<Expr>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Expr>
    struct complement<Expr, proto::tag::subscript>
    {
        template<typename Visitor>
        struct apply
          : charset_transform::BOOST_NESTED_TEMPLATE apply<
                Expr
              , dont_care
              , Visitor
            >
        {
            BOOST_MPL_ASSERT((is_same<set_initializer_type, typename proto::result_of::left<Expr>::type>));
        };

        template<typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &visitor)
        {
            return charset_transform::call(expr, dont_care(), visitor, true);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // for complementing a list-initialized set, as in ~(set= 'a','b','c')
    template<typename Expr>
    struct complement<Expr, proto::tag::comma>
    {
        // First, convert the parse tree into a set_matcher
        template<typename Visitor>
        struct apply
          : proto::terminal<
                typename proto::result_of::compile<Expr, dont_care, Visitor, lst_tag>::type
            >
        {};

        template<typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &visitor)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::compile(expr, dont_care(), visitor, lst_tag())};
            that.arg0.complement();
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Expr>
    struct complement<Expr, lookahead_tag<true> >
    {
        template<typename Visitor>
        struct apply
          : proto::unary_expr<lookahead_tag<false>, typename proto::result_of::arg<Expr>::type>
        {};

        template<typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::arg(expr)};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename Expr>
    struct complement<Expr, lookbehind_tag<true> >
    {
        template<typename Visitor>
        struct apply
          : proto::unary_expr<lookbehind_tag<false>, typename proto::result_of::arg<Expr>::type>
        {};

        template<typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            typedef typename apply<Visitor>::type type;
            type that = {proto::arg(expr)};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complementing a complement is a no-op
    template<typename Expr>
    struct complement<Expr, proto::tag::complement>
    {
        template<typename>
        struct apply
          : proto::result_of::arg<Expr>
        {};

        template<typename Visitor>
        static typename apply<Visitor>::type call(Expr const &expr, Visitor &)
        {
            return proto::arg(expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complement_transform
    struct complement_transform
    {
        template<typename Expr, typename, typename Visitor>
        struct apply
        {
            typedef complement<typename proto::result_of::arg<Expr>::type> complement;
            typedef typename complement::BOOST_NESTED_TEMPLATE apply<Visitor>::type type;
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
    struct compiler<tag::complement, xpressive::detail::seq_tag, void>
      : transform_compiler<xpressive::detail::complement_transform, xpressive::detail::seq_tag>
    {
    };

}}

#endif
