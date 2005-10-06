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

#include <vector>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/as_xpr.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    //
    template<typename XprT>
    struct use_simple_repeat;

    ///////////////////////////////////////////////////////////////////////////////
    // is_pure
    //
    template<typename XprT>
    struct is_pure;

    template<>
    struct is_pure<no_next>
      : mpl::true_
    {
    };

    template<typename MatcherT>
    struct is_pure<proto::unary_op<MatcherT, proto::noop_tag> >
      : as_matcher_type<MatcherT>::type::pure
    {
    };

    template<typename LeftT, typename RightT>
    struct is_pure<proto::binary_op<LeftT, RightT, proto::right_shift_tag> >
      : mpl::and_<is_pure<LeftT>, is_pure<RightT> >
    {
    };

    template<typename LeftT, typename RightT>
    struct is_pure<proto::binary_op<LeftT, RightT, proto::bitor_tag> >
      : mpl::and_<is_pure<LeftT>, is_pure<RightT> >
    {
    };

    template<typename RightT>
    struct is_pure<proto::binary_op<mark_tag, RightT, proto::assign_tag> >
      : mpl::false_
    {
    };

    template<typename RightT>
    struct is_pure<proto::binary_op<set_initializer_type, RightT, proto::assign_tag> >
      : mpl::true_
    {
    };

    template<typename ModifierT, typename XprT>
    struct is_pure<proto::binary_op<ModifierT, XprT, modifier_tag> >
      : is_pure<XprT>
    {
    };

    template<typename XprT, bool PositiveT>
    struct is_pure<proto::unary_op<XprT, lookahead_tag<PositiveT> > >
      : is_pure<XprT>
    {
    };

    template<typename XprT, bool PositiveT>
    struct is_pure<proto::unary_op<XprT, lookbehind_tag<PositiveT> > >
      : is_pure<XprT>
    {
    };

    template<typename XprT>
    struct is_pure<proto::unary_op<XprT, keeper_tag> >
      : is_pure<XprT>
    {
    };

    template<typename MatcherT, typename NextT>
    struct is_pure<static_xpression<MatcherT, NextT> >
      : mpl::and_<typename MatcherT::pure, is_pure<NextT> >::type
    {
    };

    template<typename BidiIterT>
    struct is_pure<shared_ptr<matchable<BidiIterT> const> >
      : mpl::false_
    {
    };

    template<typename BidiIterT>
    struct is_pure<std::vector<shared_ptr<matchable<BidiIterT> const> > >
        : mpl::false_
    {
    };

    //template<typename BidiIterT>
    //struct is_pure<basic_regex<BidiIterT> >
    //    : mpl::false_
    //{
    //};

    template<typename BidiIterT>
    struct is_pure<proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag> >
      : mpl::false_
    {
    };

    template<typename BidiIterT>
    struct is_pure<proto::unary_op<reference_wrapper<basic_regex<BidiIterT> const>, proto::noop_tag> >
      : mpl::false_
    {
    };

    // when complementing a set or an assertion, the purity is that of the set (true) or the assertion
    template<typename OpT>
    struct is_pure<proto::unary_op<OpT, proto::complement_tag> >
      : is_pure<OpT>
    {
    };

    // The comma is used in list-initialized sets, which are pure
    template<typename LeftT, typename RightT>
    struct is_pure<proto::binary_op<LeftT, RightT, proto::comma_tag> >
      : mpl::true_
    {
    };

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')]
    // It is also used for actions, which by definition have side-effects and thus are impure
    template<typename LeftT, typename RightT>
    struct is_pure<proto::binary_op<LeftT, RightT, proto::subscript_tag> >
      : is_same<LeftT, set_initializer_type>
    {
        // If LeftT is "set" then make sure that RightT is pure
        BOOST_MPL_ASSERT
        ((
            mpl::or_
            <
                mpl::not_<is_same<LeftT, set_initializer_type> >
              , is_pure<RightT>
            >
        ));
    };

    // Quantified expressions are pure IFF they use the simple_repeat_matcher

    template<typename OpT>
    struct is_pure<proto::unary_op<OpT, proto::unary_plus_tag> >
      : use_simple_repeat<OpT>
    {
    };

    template<typename OpT>
    struct is_pure<proto::unary_op<OpT, proto::unary_star_tag> >
      : use_simple_repeat<OpT>
    {
    };

    template<typename OpT>
    struct is_pure<proto::unary_op<OpT, proto::logical_not_tag> >
      : use_simple_repeat<OpT>
    {
    };

    template<typename OpT, uint_t MinT, uint_t MaxT>
    struct is_pure<proto::unary_op<OpT, generic_quant_tag<MinT, MaxT> > >
      : use_simple_repeat<OpT>
    {
    };

    template<typename OpT>
    struct is_pure<proto::unary_op<OpT, proto::unary_minus_tag> >
      : is_pure<OpT>
    {
    };

    template<typename AlternatesT>
    struct is_pure<alternates_list<AlternatesT> >
      : mpl::fold
        <
            mpl::transform_view<AlternatesT, is_pure<mpl::_1> >
          , mpl::true_
          , mpl::and_<mpl::_1, mpl::_2>
        >::type
    {
    };


    ///////////////////////////////////////////////////////////////////////////////
    // use_simple_repeat
    // BUGBUG this doesn't handle +(_ >> s1) correctly, right?
    template<typename XprT>
    struct use_simple_repeat
      : mpl::and_<mpl::not_equal_to<width_of<XprT>, unknown_width>, is_pure<XprT> >
    {
        // should never try to quantify something of 0-width
        BOOST_MPL_ASSERT((mpl::not_equal_to<width_of<XprT>, mpl::size_t<0> >));
    };

    template<typename MatcherT>
    struct use_simple_repeat<proto::unary_op<MatcherT, proto::noop_tag> >
      : mpl::and_
        <
            mpl::equal_to
            <
                quant_type<typename as_matcher_type<MatcherT>::type>
              , mpl::int_<quant_fixed_width>
            >
          , typename as_matcher_type<MatcherT>::type::pure
        >
    {
        BOOST_MPL_ASSERT_RELATION(0, !=, as_matcher_type<MatcherT>::type::width::value);
    };

    template<typename OpT, typename ArgT>
    struct is_pure<proto::op_proxy<OpT, ArgT> >
      : is_pure<OpT>
    {
    };

}}} // namespace boost::xpressive::detail

#endif
