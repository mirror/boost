///////////////////////////////////////////////////////////////////////////////
// width_of.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_WIDTH_OF_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_WIDTH_OF_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/mpl/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/as_xpr.hpp>

///////////////////////////////////////////////////////////////////////////////
// add widths
#define BOOST_XPR_ADD_WIDTH_(X, Y)                                                                  \
    mpl::size_t                                                                                     \
    <                                                                                               \
        X::value == unknown_width::value || Y::value == unknown_width::value                        \
      ? unknown_width::value                                                                        \
      : X::value + Y::value                                                                         \
    >

///////////////////////////////////////////////////////////////////////////////
// multiply widths
#define BOOST_XPR_MULT_WIDTH_(X, Y)                                                                 \
    mpl::size_t                                                                                     \
    <                                                                                               \
        X::value == unknown_width::value || Y::value == unknown_width::value                        \
      ? unknown_width::value                                                                        \
      : X::value * Y::value                                                                         \
    >

///////////////////////////////////////////////////////////////////////////////
// check widths for equality
#define BOOST_XPR_EQUAL_WIDTH_(X, Y)                                                                \
    mpl::size_t                                                                                     \
    <                                                                                               \
        X::value == Y::value                                                                        \
      ? X::value                                                                                    \
      : unknown_width::value                                                                        \
    >

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // width_of
    //
    template<typename Node>
    struct width_of;

    template<typename Node>
    struct width_of<Node &>
      : width_of<Node>
    {};

    template<typename Node>
    struct width_of<Node const>
      : width_of<Node>
    {};

    template<typename Matcher>
    struct width_of<proto::unary_op<Matcher, proto::noop_tag> >
      : mpl::size_t<as_matcher<Matcher>::type::width>
    {};

    template<typename Left, typename Right>
    struct width_of<proto::binary_op<Left, Right, proto::right_shift_tag> >
      : BOOST_XPR_ADD_WIDTH_(width_of<Left>, width_of<Right>)
    {};

    template<typename Left, typename Right>
    struct width_of<proto::binary_op<Left, Right, proto::bitor_tag> >
      : BOOST_XPR_EQUAL_WIDTH_(width_of<Left>, width_of<Right>)
    {};

    template<typename Right>
    struct width_of<proto::binary_op<mark_tag const, Right, proto::assign_tag> >
      : width_of<Right>
    {};

    template<typename Right>
    struct width_of<proto::binary_op<set_initializer_type const, Right, proto::assign_tag> >
      : mpl::size_t<1>
    {};

    template<typename Modifier, typename Node>
    struct width_of<proto::binary_op<Modifier, Node, modifier_tag> >
      : width_of<Node>
    {};

    template<typename Node, bool Positive>
    struct width_of<proto::unary_op<Node, lookahead_tag<Positive> > >
      : mpl::size_t<0>
    {};

    template<typename Node, bool Positive>
    struct width_of<proto::unary_op<Node, lookbehind_tag<Positive> > >
      : mpl::size_t<0>
    {};

    // keep() is used to turn off backtracking, so they should only be used
    // for things that are variable-width (eg. quantified)
    template<typename Node>
    struct width_of<proto::unary_op<Node, keeper_tag> >
      : unknown_width
    {
        // If this assert fires, you put something that doesn't require backtracking
        // in a keep(). In that case, the keep() is not necessary and you should just
        // remove it.
        BOOST_MPL_ASSERT_RELATION(width_of<Node>::value, ==, unknown_width::value);
    };

    template<typename Node>
    struct width_of<proto::unary_op<Node, proto::unary_plus_tag> >
      : unknown_width
    {};

    template<typename Node>
    struct width_of<proto::unary_op<Node, proto::unary_star_tag> >
      : unknown_width
    {};

    template<typename Node>
    struct width_of<proto::unary_op<Node, proto::logical_not_tag> >
      : unknown_width
    {};

    template<typename Node, uint_t Min, uint_t Max>
    struct width_of<proto::unary_op<Node, generic_quant_tag<Min, Max> > >
      : unknown_width
    {};

    template<typename Node, uint_t Count>
    struct width_of<proto::unary_op<Node, generic_quant_tag<Count, Count> > >
      : BOOST_XPR_MULT_WIDTH_(width_of<Node>, mpl::size_t<Count>)
    {};

    template<typename Node>
    struct width_of<proto::unary_op<Node, proto::unary_minus_tag> >
      : width_of<Node>
    {};

    // when complementing a set or an assertion, the width is that of the set (1) or the assertion (0)
    template<typename Node>
    struct width_of<proto::unary_op<Node, proto::complement_tag> >
      : width_of<Node>
    {};

    // The comma is used in list-initialized sets, and the width of sets are 1
    template<typename Left, typename Right>
    struct width_of<proto::binary_op<Left, Right, proto::comma_tag> >
      : mpl::size_t<1>
    {};

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')], 
    // or for actions as in (any >> expr)[ action ]
    template<typename Left, typename Right>
    struct width_of<proto::binary_op<Left, Right, proto::subscript_tag> >
      : width_of<Left>
    {};

    template<typename Right>
    struct width_of<proto::binary_op<set_initializer_type const, Right, proto::subscript_tag> >
      : mpl::size_t<1>
    {
        // If Left is "set" then make sure that Right has a width_of 1
        BOOST_MPL_ASSERT_RELATION(1, ==, width_of<Right>::value);
    };

    template<typename Node, typename Arg>
    struct width_of<proto::op_proxy<Node, Arg> >
      : width_of<Node>
    {};

}}} // namespace boost::xpressive::detail

#endif
