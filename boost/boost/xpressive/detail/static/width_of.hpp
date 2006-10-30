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
    template<typename Expr>
    struct width_of;

    template<typename Tag, typename Arg0, typename Arg1>
    struct width_of_impl;

    template<typename Matcher>
    struct width_of_impl<proto::terminal_tag, Matcher, void>
      : mpl::size_t<as_matcher_type<Matcher>::type::width>
    {};

    template<typename Left, typename Right>
    struct width_of_impl<proto::right_shift_tag, Left, Right>
      : BOOST_XPR_ADD_WIDTH_(width_of<Left>, width_of<Right>)
    {};

    template<typename Left, typename Right>
    struct width_of_impl<proto::bitor_tag, Left, Right>
      : BOOST_XPR_EQUAL_WIDTH_(width_of<Left>, width_of<Right>)
    {};

    template<typename Right>
    struct width_of_impl<proto::assign_tag, mark_tag, Right>
      : width_of<Right>
    {};

    template<typename Right>
    struct width_of_impl<proto::assign_tag, set_initializer_type, Right>
      : mpl::size_t<1>
    {};

    template<typename Modifier, typename Expr>
    struct width_of_impl<modifier_tag, Modifier, Expr>
      : width_of<Expr>
    {};

    template<typename Expr, bool Positive>
    struct width_of_impl<lookahead_tag<Positive>, Expr, void>
      : mpl::size_t<0>
    {};

    template<typename Expr, bool Positive>
    struct width_of_impl<lookbehind_tag<Positive>, Expr, void>
      : mpl::size_t<0>
    {};

    // keep() is used to turn off backtracking, so they should only be used
    // for things that are variable-width (eg. quantified)
    template<typename Expr>
    struct width_of_impl<keeper_tag, Expr, void>
      : unknown_width
    {
        // If this assert fires, you put something that doesn't require backtracking
        // in a keep(). In that case, the keep() is not necessary and you should just
        // remove it.
        BOOST_MPL_ASSERT_RELATION(width_of<Expr>::value, ==, unknown_width::value);
    };

    template<typename Expr>
    struct width_of_impl<proto::unary_plus_tag, Expr, void>
      : unknown_width
    {};

    template<typename Expr>
    struct width_of_impl<proto::unary_star_tag, Expr, void>
      : unknown_width
    {};

    template<typename Expr>
    struct width_of_impl<proto::logical_not_tag, Expr, void>
      : unknown_width
    {};

    template<typename Expr, uint_t Min, uint_t Max>
    struct width_of_impl<generic_quant_tag<Min, Max>, Expr, void>
      : unknown_width
    {};

    template<typename Expr, uint_t Count>
    struct width_of_impl<generic_quant_tag<Count, Count>, Expr, void>
      : BOOST_XPR_MULT_WIDTH_(width_of<Expr>, mpl::size_t<Count>)
    {};

    template<typename Expr>
    struct width_of_impl<proto::unary_minus_tag, Expr, void>
      : width_of<Expr>
    {};

    // when complementing a set or an assertion, the width is that of the set (1) or the assertion (0)
    template<typename Expr>
    struct width_of_impl<proto::complement_tag, Expr, void>
      : width_of<Expr>
    {};

    // The comma is used in list-initialized sets, and the width of sets are 1
    template<typename Left, typename Right>
    struct width_of_impl<proto::comma_tag, Left, Right>
      : mpl::size_t<1>
    {};

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')], 
    // or for actions as in (any >> expr)[ action ]
    template<typename Left, typename Right>
    struct width_of_impl<proto::subscript_tag, Left, Right>
      : width_of<Left>
    {};

    template<typename Right>
    struct width_of_impl<proto::subscript_tag, set_initializer_type, Right>
      : mpl::size_t<1>
    {
        // If Left is "set" then make sure that Right has a width_of 1
        BOOST_MPL_ASSERT_RELATION(1, ==, width_of<Right>::value);
    };

    // width_of
    template<typename Expr>
    struct width_of
      : width_of_impl<
            typename Expr::tag_type
          , typename proto::meta::unref<typename Expr::arg0_type>::type
          , typename proto::meta::unref<typename Expr::arg1_type>::type
        >
    {};

}}} // namespace boost::xpressive::detail

#endif
