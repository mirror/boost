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

    ///////////////////////////////////////////////////////////////////////////////
    // complement
    //   the result of applying operator~ to various expressions
    template<typename OpT, typename VisitorT>
    struct complement
    {
        // If your compile breaks here, then you are applying the complement operator ~
        // to something that does not support it. For instance, ~(_ >> 'a') will trigger this
        // assertion because the sub-expression (_ >> 'a') has no complement.
        BOOST_MPL_ASSERT((never_true<OpT>));
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename CharT, bool NotT, typename VisitorT>
    struct complement<proto::unary_op<literal_placeholder<CharT, NotT>, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<literal_placeholder<CharT, !NotT>, proto::noop_tag> type;

        static type const call(proto::unary_op<literal_placeholder<CharT, NotT>, proto::noop_tag> const &op, VisitorT &)
        {
            literal_placeholder<CharT, !NotT> literal = proto::arg(op).ch_;
            return proto::noop(literal);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename CharT, typename VisitorT>
    struct complement<proto::unary_op<CharT, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<literal_placeholder<CharT, true>, proto::noop_tag> type;

        static type const call(proto::unary_op<CharT, proto::noop_tag> const &op, VisitorT &)
        {
            literal_placeholder<CharT, true> literal = proto::arg(op);
            return proto::noop(literal);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename TraitsT, int SizeT, typename VisitorT>
    struct complement<proto::unary_op<set_matcher<TraitsT, SizeT>, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<set_matcher<TraitsT, SizeT>, proto::noop_tag> type;

        static type const call(proto::unary_op<set_matcher<TraitsT, SizeT>, proto::noop_tag> const &op, VisitorT &)
        {
            set_matcher<TraitsT, SizeT> set = proto::arg(op);
            set.complement();
            return proto::noop(set);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename VisitorT>
    struct complement<proto::unary_op<posix_charset_placeholder, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<posix_charset_placeholder, proto::noop_tag> type;

        static type const call(proto::unary_op<posix_charset_placeholder, proto::noop_tag> const &op, VisitorT &)
        {
            posix_charset_placeholder posix = proto::arg(op);
            posix.not_ = !posix.not_;
            return proto::noop(posix);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename OpT, typename VisitorT>
    struct complement<proto::binary_op<set_initializer_type, OpT, proto::subscript_tag>, VisitorT>
    {
        typedef typename charset_transform::BOOST_NESTED_TEMPLATE apply
        <
            proto::binary_op<set_initializer_type, OpT, proto::subscript_tag>
          , dont_care
          , VisitorT
        >::type type;

        static type call(proto::binary_op<set_initializer_type, OpT, proto::subscript_tag> const &op, VisitorT &visitor)
        {
            return charset_transform::call(op, dont_care(), visitor, true);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // for complementing a list-initialized set, as in ~(set= 'a','b','c')
    template<typename LeftT, typename RightT, typename VisitorT>
    struct complement<proto::binary_op<LeftT, RightT, proto::comma_tag>, VisitorT>
    {
        // First, convert the parse tree into a set_matcher
        typedef typename proto::compiler<proto::comma_tag, lst_tag>::BOOST_NESTED_TEMPLATE apply
        <
            proto::binary_op<LeftT, RightT, proto::comma_tag>
          , dont_care
          , VisitorT
        >::type set_matcher;

        typedef proto::unary_op<set_matcher, proto::noop_tag> type;

        static type const call(proto::binary_op<LeftT, RightT, proto::comma_tag> const &op, VisitorT &visitor)
        {
            set_matcher set(proto::compile(op, dont_care(), visitor, lst_tag()));
            set.complement();
            return proto::noop(set);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename OpT, typename VisitorT>
    struct complement<proto::unary_op<OpT, lookahead_tag<true> >, VisitorT>
    {
        typedef proto::unary_op<OpT, lookahead_tag<false> > type;

        static type call(proto::unary_op<OpT, lookahead_tag<true> > const &op, VisitorT &)
        {
            return proto::make_op<lookahead_tag<false> >(proto::arg(op));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename OpT, typename VisitorT>
    struct complement<proto::unary_op<OpT, lookbehind_tag<true> >, VisitorT>
    {
        typedef proto::unary_op<OpT, lookbehind_tag<false> > type;

        static type call(proto::unary_op<OpT, lookbehind_tag<true> > const &op, VisitorT &)
        {
            return proto::make_op<lookbehind_tag<false> >(proto::arg(op));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename VisitorT>
    struct complement<proto::unary_op<assert_word_placeholder<word_boundary<true> >, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<assert_word_placeholder<word_boundary<false> >, proto::noop_tag> type;

        static type call(proto::unary_op<assert_word_placeholder<word_boundary<true> >, proto::noop_tag> const &, VisitorT &)
        {
            return proto::noop(assert_word_placeholder<word_boundary<false> >());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename VisitorT>
    struct complement<logical_newline_xpression, VisitorT>
    {
        typedef proto::binary_op
        <
            proto::unary_op<logical_newline_xpression, lookahead_tag<false> >
          , proto::unary_op<any_matcher, proto::noop_tag>
          , proto::right_shift_tag
        > type;

        static type call(logical_newline_xpression const &op, VisitorT &)
        {
            return proto::make_op<lookahead_tag<false> >(op) >> proto::noop(any_matcher());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complementing a complement is a no-op
    template<typename ArgT, typename VisitorT>
    struct complement<proto::unary_op<ArgT, proto::complement_tag>, VisitorT>
    {
        typedef ArgT type;

        static ArgT const &call(proto::unary_op<ArgT, proto::complement_tag> const &op, VisitorT &)
        {
            return proto::arg(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    //
    template<typename CharT, typename VisitorT>
    struct complement<proto::unary_op<range_placeholder<CharT>, proto::noop_tag>, VisitorT>
    {
        typedef proto::unary_op<range_placeholder<CharT>, proto::noop_tag> type;

        static type const call(proto::unary_op<range_placeholder<CharT>, proto::noop_tag> const &op, VisitorT &)
        {
            range_placeholder<CharT> rng = proto::arg(op);
            rng.not_ = !rng.not_;
            return proto::noop(rng);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // complement_transform
    struct complement_transform
    {
        template<typename OpT, typename, typename VisitorT>
        struct apply
        {
            typedef typename complement<typename proto::arg_type<OpT>::type, VisitorT>::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename complement<typename proto::arg_type<OpT>::type, VisitorT>::type
        call(OpT const &op, StateT const &, VisitorT &visitor)
        {
            return complement<typename proto::arg_type<OpT>::type, VisitorT>::call(proto::arg(op), visitor);
        }
    };

}}}

namespace boost { namespace proto
{

    template<>
    struct compiler<complement_tag, xpressive::detail::seq_tag>
      : transform_compiler<xpressive::detail::complement_transform, xpressive::detail::seq_tag>
    {
    };

}}

#endif
