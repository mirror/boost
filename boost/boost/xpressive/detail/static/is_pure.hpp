///////////////////////////////////////////////////////////////////////////////
// is_pure.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_IS_PURE_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_IS_PURE_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/as_xpr.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>

///////////////////////////////////////////////////////////////////////////////
// equivalent to mpl::and_<X, Y>
#define BOOST_XPR_AND_PURE_(X, Y)                                                                   \
    mpl::bool_<X::value && Y::value>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    //
    template<typename Expr, typename Tag = typename Expr::tag_type>
    struct use_simple_repeat;

    ///////////////////////////////////////////////////////////////////////////////
    // is_pure
    //
    template<typename Expr>
    struct is_pure;

    template<typename Tag, typename Arg0, typename Arg1>
    struct is_pure_impl;

    template<typename Matcher>
    struct is_pure_impl<proto::terminal_tag, Matcher, void>
      : mpl::bool_<as_matcher_type<Matcher>::type::pure>
    {};

    template<typename Left, typename Right>
    struct is_pure_impl<proto::right_shift_tag, Left, Right>
      : BOOST_XPR_AND_PURE_(is_pure<Left>, is_pure<Right>)
    {};

    template<typename Left, typename Right>
    struct is_pure_impl<proto::bitor_tag, Left, Right>
      : BOOST_XPR_AND_PURE_(is_pure<Left>, is_pure<Right>)
    {};

    template<typename Right>
    struct is_pure_impl<proto::assign_tag, basic_mark_tag, Right>
      : mpl::false_
    {};

    template<typename Right>
    struct is_pure_impl<proto::assign_tag, set_initializer_type, Right>
      : mpl::true_
    {};

    template<typename Modifier, typename Expr>
    struct is_pure_impl<modifier_tag, Modifier, Expr>
      : is_pure<Expr>
    {};

    template<typename Expr, bool Positive>
    struct is_pure_impl<lookahead_tag<Positive>, Expr, void>
      : is_pure<Expr>
    {};

    template<typename Expr, bool Positive>
    struct is_pure_impl<lookbehind_tag<Positive>, Expr, void>
      : is_pure<Expr>
    {};

    template<typename Expr>
    struct is_pure_impl<keeper_tag, Expr, void>
      : is_pure<Expr>
    {};

    // when complementing a set or an assertion, the purity is that of the set (true) or the assertion
    template<typename Expr>
    struct is_pure_impl<proto::complement_tag, Expr, void>
      : is_pure<Expr>
    {};

    // The comma is used in list-initialized sets, which are pure
    template<typename Left, typename Right>
    struct is_pure_impl<proto::comma_tag, Left, Right>
      : mpl::true_
    {};

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')]
    // It is also used for actions, which by definition have side-effects and thus are impure
    template<typename Left, typename Right>
    struct is_pure_impl<proto::subscript_tag, Left, Right>
      : mpl::false_
    {};

    template<typename Right>
    struct is_pure_impl<proto::subscript_tag, set_initializer_type, Right>
      : mpl::true_
    {
        // If Left is "set" then make sure that Right is pure
        BOOST_MPL_ASSERT((is_pure<Right>));
    };

    // Quantified expressions are pure IFF they use the simple_repeat_matcher
    template<typename Expr>
    struct is_pure_impl<proto::unary_plus_tag, Expr, void>
      : use_simple_repeat<Expr>
    {};

    template<typename Expr>
    struct is_pure_impl<proto::unary_star_tag, Expr, void>
      : use_simple_repeat<Expr>
    {};

    template<typename Expr>
    struct is_pure_impl<proto::logical_not_tag, Expr, void>
      : use_simple_repeat<Expr>
    {};

    template<typename Expr, uint_t Min, uint_t Max>
    struct is_pure_impl<generic_quant_tag<Min, Max>, Expr, void>
      : use_simple_repeat<Expr>
    {};

    template<typename Expr>
    struct is_pure_impl<proto::unary_minus_tag, Expr, void>
      : is_pure<Expr>
    {};

    // simple_repeat_helper
    template<bool B, quant_enum Q>
    struct use_simple_repeat_helper
      : mpl::false_
    {};

    template<>
    struct use_simple_repeat_helper<true, quant_fixed_width>
      : mpl::true_
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    //  TODO this doesn't optimize +(_ >> "hello")
    template<typename Expr, typename Tag>
    struct use_simple_repeat
      : mpl::bool_<width_of<Expr>::value != unknown_width::value && is_pure<Expr>::value>
    {
        // should never try to repeat something of 0-width
        //BOOST_MPL_ASSERT_RELATION(0, !=, width_of<Expr>::value);
        BOOST_STATIC_ASSERT(0 != width_of<Expr>::value);
    };

    template<typename Expr>
    struct use_simple_repeat<Expr, proto::terminal_tag>
      : use_simple_repeat_helper<
            as_matcher_type<typename Expr::arg0_type>::type::pure
          , as_matcher_type<typename Expr::arg0_type>::type::quant
        >
    {
        //BOOST_MPL_ASSERT_RELATION(0, !=, as_matcher_type<typename Expr::arg0_type>::type::width);
        BOOST_STATIC_ASSERT(0 != as_matcher_type<typename Expr::arg0_type>::type::width);
    };

    // is_pure
    template<typename Expr>
    struct is_pure
      : is_pure_impl<
            typename Expr::tag_type
          , typename proto::meta::unref<typename Expr::arg0_type>::type
          , typename proto::meta::unref<typename Expr::arg1_type>::type
        >
    {};

}}} // namespace boost::xpressive::detail

#endif
