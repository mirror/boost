///////////////////////////////////////////////////////////////////////////////
// marker_transform.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MARKER_TRANSFORM_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MARKER_TRANSFORM_HPP_EAN_10_04_2005

#include <boost/mpl/bool.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // is_marker
    template<typename OpT>
    struct is_marker
      : mpl::false_
    {};

    template<typename OpT>
    struct is_marker
    <
        proto::binary_op
        <
            proto::unary_op<mark_begin_matcher, proto::noop_tag>
          , OpT
          , proto::right_shift_tag
        >
    >
      : mpl::true_
    {};

    ///////////////////////////////////////////////////////////////////////////////
    // mark_number
    template<typename OpT, typename VisitorT>
    int mark_number
    (
        proto::binary_op
        <
            proto::unary_op<mark_begin_matcher, proto::noop_tag>
          , OpT
          , proto::right_shift_tag
        > const &op
      , VisitorT &
    )
    {
        return proto::arg(proto::left(op)).mark_number_;
    }

    template<typename ArgT, typename VisitorT>
    int mark_number(ArgT const &, VisitorT &visitor)
    {
        return visitor.get_hidden_mark();
    }

    ///////////////////////////////////////////////////////////////////////////////
    // marker_transform
    //   Insert mark tags before and after the expression
    struct marker_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            typedef proto::binary_op
            <
                proto::unary_op<mark_begin_matcher, proto::noop_tag>
              , proto::binary_op
                <
                    OpT
                  , proto::unary_op<mark_end_matcher, proto::noop_tag>
                  , proto::right_shift_tag
                >
              , proto::right_shift_tag
            > type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &, VisitorT &visitor, int mark_nbr = -1)
        {
            return proto::noop(mark_begin_matcher(mark_nbr))
                >> (op >> proto::noop(mark_end_matcher(mark_nbr)));
        }
    };

}}}

#endif
