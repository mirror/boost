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

#include <vector>
#include <boost/ref.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/as_xpr.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // add_width
    template<typename X, typename Y>
    struct add_width
      : mpl::eval_if
        <
            mpl::or_
            <
                mpl::equal_to<X, unknown_width>
              , mpl::equal_to<Y, unknown_width>
            >
          , mpl::identity<unknown_width>
          , mpl::plus<X, Y>
        >::type
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // mult_width
    template<typename X, typename Y>
    struct mult_width
      : mpl::eval_if
        <
            mpl::or_
            <
                mpl::equal_to<X, unknown_width>
              , mpl::equal_to<Y, unknown_width>
            >
          , mpl::identity<unknown_width>
          , mpl::times<X, Y>
        >::type
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // equal_width
    template<typename X, typename Y>
    struct equal_width
      : mpl::if_
        <
            mpl::equal_to<X, Y>
          , X
          , unknown_width
        >::type
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // width_of
    //
    template<typename XprT>
    struct width_of;

    template<>
    struct width_of<no_next>
      : mpl::size_t<0>
    {
    };

    template<typename MatcherT>
    struct width_of<proto::unary_op<MatcherT, proto::noop_tag> >
      : as_matcher_type<MatcherT>::type::width
    {
    };

    template<typename LeftT, typename RightT>
    struct width_of<proto::binary_op<LeftT, RightT, proto::right_shift_tag> >
      : add_width<width_of<LeftT>, width_of<RightT> >
    {
    };

    template<typename LeftT, typename RightT>
    struct width_of<proto::binary_op<LeftT, RightT, proto::bitor_tag> >
      : equal_width<width_of<LeftT>, width_of<RightT> >
    {
    };

    template<typename RightT>
    struct width_of<proto::binary_op<mark_tag, RightT, proto::assign_tag> >
      : width_of<RightT>
    {
    };

    template<typename RightT>
    struct width_of<proto::binary_op<set_initializer_type, RightT, proto::assign_tag> >
      : mpl::size_t<1>
    {
    };

    template<typename ModifierT, typename XprT>
    struct width_of<proto::binary_op<ModifierT, XprT, modifier_tag> >
      : width_of<XprT>
    {
    };

    template<typename XprT, bool PositiveT>
    struct width_of<proto::unary_op<XprT, lookahead_tag<PositiveT> > >
      : mpl::size_t<0>
    {
    };

    template<typename XprT, bool PositiveT>
    struct width_of<proto::unary_op<XprT, lookbehind_tag<PositiveT> > >
      : mpl::size_t<0>
    {
    };

    template<typename XprT>
    struct width_of<proto::unary_op<XprT, keeper_tag> >
      : width_of<XprT>
    {
    };

    template<typename MatcherT, typename NextT>
    struct width_of<static_xpression<MatcherT, NextT> >
      : add_width<typename MatcherT::width, width_of<NextT> >
    {
    };

    template<typename BidiIterT>
    struct width_of<shared_ptr<matchable<BidiIterT> const> >
      : unknown_width
    {
    };

    template<typename BidiIterT>
    struct width_of<std::vector<shared_ptr<matchable<BidiIterT> const> > >
      : unknown_width
    {
    };

    template<typename BidiIterT>
    struct width_of<proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag> >
      : unknown_width
    {
    };

    template<typename BidiIterT>
    struct width_of<proto::unary_op<reference_wrapper<basic_regex<BidiIterT> const>, proto::noop_tag> >
      : unknown_width
    {
    };

    template<typename OpT>
    struct width_of<proto::unary_op<OpT, proto::unary_plus_tag> >
      : unknown_width
    {
    };

    template<typename OpT>
    struct width_of<proto::unary_op<OpT, proto::unary_star_tag> >
      : unknown_width
    {
    };

    template<typename OpT>
    struct width_of<proto::unary_op<OpT, proto::logical_not_tag> >
      : unknown_width
    {
    };

    template<typename OpT, uint_t MinT, uint_t MaxT>
    struct width_of<proto::unary_op<OpT, generic_quant_tag<MinT, MaxT> > >
      : mpl::if_c<MinT==MaxT, mult_width<width_of<OpT>, mpl::size_t<MinT> >, unknown_width>::type
    {
    };

    template<typename OpT>
    struct width_of<proto::unary_op<OpT, proto::unary_minus_tag> >
      : width_of<OpT>
    {
    };

    // when complementing a set or an assertion, the width is that of the set (1) or the assertion (0)
    template<typename OpT>
    struct width_of<proto::unary_op<OpT, proto::complement_tag> >
      : width_of<OpT>
    {
    };

    // The comma is used in list-initialized sets, and the width of sets are 1
    template<typename LeftT, typename RightT>
    struct width_of<proto::binary_op<LeftT, RightT, proto::comma_tag> >
      : mpl::size_t<1>
    {
    };

    // The subscript operator[] is used for sets, as in set['a' | range('b','h')], 
    // or for actions as in (any >> expr)[ action ]
    template<typename LeftT, typename RightT>
    struct width_of<proto::binary_op<LeftT, RightT, proto::subscript_tag> >
      : mpl::if_<is_same<LeftT, set_initializer_type>, mpl::size_t<1>, width_of<LeftT> >::type
    {
        // If LeftT is "set" then make sure that RightT has a width_of 1
        BOOST_MPL_ASSERT
        ((
            mpl::or_
            <
                mpl::not_<is_same<LeftT, set_initializer_type> >
              , mpl::equal_to<width_of<RightT>, mpl::size_t<1> >
            >
        ));
    };

    // The width of a list of alternates is N if all the alternates have width N, otherwise unknown_width
    template<typename WidthsT>
    struct alt_width_of
      : mpl::fold
        <
            WidthsT
          , typename mpl::front<WidthsT>::type
          , equal_width<mpl::_1, mpl::_2>
        >::type
    {
    };

    template<typename AlternatesT>
    struct width_of<alternates_list<AlternatesT> >
      : alt_width_of<mpl::transform_view<AlternatesT, width_of<mpl::_1> > >
    {
    };

    template<typename OpT, typename ArgT>
    struct width_of<proto::op_proxy<OpT, ArgT> >
      : width_of<OpT>
    {
    };

}}} // namespace boost::xpressive::detail

#endif
