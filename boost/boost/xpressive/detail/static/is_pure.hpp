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

#include <boost/ref.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>

///////////////////////////////////////////////////////////////////////////////
// equivalent to mpl::and_<X, Y>
#define BOOST_XPR_AND_PURE_(X, Y)                                                                   \
    mpl::and_<X, Y >

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    //
    template<typename Expr>
    struct use_simple_repeat;

    ///////////////////////////////////////////////////////////////////////////////
    // is_terminal_pure
    //
    template<typename Expr, bool IsXpr = is_xpr<Expr>::value>
    struct is_terminal_pure
      : mpl::bool_<Expr::pure>  // xpression types
    {};

    template<typename Expr>
    struct is_terminal_pure<Expr, false>
      : mpl::true_      // char literals
    {};

    template<typename Expr>
    struct is_terminal_pure<Expr *, false>
      : mpl::true_      // string literals
    {};

    template<typename Char, std::size_t N>
    struct is_terminal_pure<Char (&) [N], false>
      : mpl::true_      // string literals
    {};

    template<typename Char, std::size_t N>
    struct is_terminal_pure<Char const (&) [N], false>
      : mpl::true_      // string literals
    {};

    template<typename BidiIter>
    struct is_terminal_pure<tracking_ptr<regex_impl<BidiIter> >, false>
      : mpl::false_     // basic_regex
    {};

    template<typename BidiIter>
    struct is_terminal_pure<reference_wrapper<basic_regex<BidiIter> >, false>
      : mpl::false_     // basic_regex
    {};

    template<typename BidiIter>
    struct is_terminal_pure<reference_wrapper<basic_regex<BidiIter> const>, false>
      : mpl::false_     // basic_regex
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // is_pure
    //
    template<typename Expr, typename Tag = typename Expr::tag_type>
    struct is_pure {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::terminal>
      : is_terminal_pure<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::shift_right>
      : BOOST_XPR_AND_PURE_(
            is_pure<typename proto::result_of::left<Expr>::type>
          , is_pure<typename proto::result_of::right<Expr>::type>
        )
    {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::bitwise_or>
      : BOOST_XPR_AND_PURE_(
            is_pure<typename proto::result_of::left<Expr>::type>
          , is_pure<typename proto::result_of::right<Expr>::type>
        )
    {};

    template<typename Left>
    struct is_pure_assign {};

    template<>
    struct is_pure_assign<basic_mark_tag>
      : mpl::false_
    {};

    template<>
    struct is_pure_assign<set_initializer_type>
      : mpl::true_
    {};

    // either (s1 = ...) or (set = ...)
    template<typename Expr>
    struct is_pure<Expr, proto::tag::assign>
      : is_pure_assign<typename proto::result_of::left<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, modifier_tag>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, lookahead_tag>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, lookbehind_tag>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, keeper_tag>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    // when complementing a set or an assertion, the purity is that of the set (true) or the assertion
    template<typename Expr>
    struct is_pure<Expr, proto::tag::complement>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    // The comma is used in list-initialized sets, which are pure
    template<typename Expr>
    struct is_pure<Expr, proto::tag::comma>
      : mpl::true_
    {};

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')]
    // It is also used for actions, which by definition have side-effects and thus are impure
    template<typename Expr, typename Left>
    struct is_pure_subscript
      : mpl::false_
    {};

    template<typename Expr>
    struct is_pure_subscript<Expr, set_initializer_type>
      : mpl::true_
    {
        // If Left is "set" then make sure that Right is pure
        BOOST_MPL_ASSERT((is_pure<typename proto::result_of::right<Expr>::type>));
    };

    template<typename Expr>
    struct is_pure<Expr, proto::tag::subscript>
      : is_pure_subscript<Expr, typename proto::result_of::left<Expr>::type>
    {};

    // Quantified expressions are pure IFF they use the simple_repeat_matcher
    template<typename Expr>
    struct is_pure<Expr, proto::tag::posit>
      : use_simple_repeat<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::dereference>
      : use_simple_repeat<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::logical_not>
      : use_simple_repeat<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr, uint_t Min, uint_t Max>
    struct is_pure<Expr, generic_quant_tag<Min, Max> >
      : use_simple_repeat<typename proto::result_of::arg<Expr>::type>
    {};

    template<typename Expr>
    struct is_pure<Expr, proto::tag::negate>
      : is_pure<typename proto::result_of::arg<Expr>::type>
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    //
    template<typename Expr>
    struct use_simple_repeat
      : mpl::bool_<width_of<Expr>::value != unknown_width::value && is_pure<Expr>::value>
    {
        // should never try to repeat something of 0-width
        BOOST_MPL_ASSERT_RELATION(0, !=, width_of<Expr>::value);
    };

}}} // namespace boost::xpressive::detail

#endif
