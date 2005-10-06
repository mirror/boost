///////////////////////////////////////////////////////////////////////////////
// quant_transforms.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_QUANT_TRANSFORMS_HPP_EAN_10_04_2005

#include <limits.h>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/width_of.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/static/productions/quant_traits.hpp>
#include <boost/xpressive/detail/static/productions/marker_transform.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // plus_no_mark_transform
    //   Unary plus becomes a quantifier by wrapping arg in begin/end quantifiers
    template<bool GreedyT = true, uint_t MinT = 1, uint_t MaxT = UINT_MAX-1>
    struct plus_no_mark_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<OpT>::type> >));

            typedef proto::binary_op
            <
                proto::binary_op
                <
                    proto::unary_op<repeat_begin_matcher, proto::noop_tag>
                  , typename proto::arg_type<OpT>::type // skip the "plus" node
                  , proto::right_shift_tag
                >
              , proto::unary_op<repeat_end_matcher<GreedyT>, proto::noop_tag>
              , proto::right_shift_tag
            > type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &, VisitorT &, int mark_number = -1, uint_t min = MinT, uint_t max = MaxT)
        {
            return proto::noop(repeat_begin_matcher(mark_number))
                >> proto::arg(op)
                >> proto::noop(repeat_end_matcher<GreedyT>(mark_number, min, max));
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // plus_mark_transform
    //   compose the quant and mark transforms
    template<bool GreedyT = true, uint_t MinT = 1, uint_t MaxT = UINT_MAX-1>
    struct plus_mark_transform
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<OpT>::type> >));

            typedef typename marker_transform::apply
            <
                typename proto::arg_type<OpT>::type
              , StateT
              , VisitorT
            >::type marker_type;

            typedef typename plus_no_mark_transform<GreedyT, MinT, MaxT>::BOOST_NESTED_TEMPLATE apply
            <
            proto::unary_op<marker_type, typename proto::tag_type<OpT>::type>
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor, int mark_number = -1, uint_t min = MinT, uint_t max = MaxT)
        {
            return plus_no_mark_transform<GreedyT, MinT, MaxT>::call
            (
                proto::make_op<typename proto::tag_type<OpT>::type>
                (
                    marker_transform::call(proto::arg(op), state, visitor, mark_number)
                )
              , state
              , visitor
              , mark_number
              , min
              , max
            );
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // optional_transform
    //   An optional expression gets the following transformation:
    template<bool GreedyT>
    struct optional_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<OpT>::type> >));

            typedef proto::binary_op
            <
                typename proto::arg_type<OpT>::type
              , proto::unary_op<epsilon_matcher, proto::noop_tag>
              , proto::bitor_tag
            > type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &, VisitorT &)
        {
            return proto::arg(op) | proto::noop(epsilon_matcher());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // non-greedy optional transform
    template<>
    struct optional_transform<false>
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<typename proto::arg_type<OpT>::type> >));

            typedef proto::binary_op
            <
                proto::unary_op<epsilon_matcher, proto::noop_tag>
              , typename proto::arg_type<OpT>::type
              , proto::bitor_tag
            > type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &, VisitorT &)
        {
            return proto::noop(epsilon_matcher()) | proto::arg(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // simple_repeat_branch
    template<bool GreedyT = true, uint_t MinT = 0, uint_t MaxT = UINT_MAX-1>
    struct simple_repeat_branch
    {
        typedef true_xpression state_type;

        template<typename OpT, typename StateT, typename>
        struct apply
        {
            BOOST_MPL_ASSERT((mpl::not_equal_to<mpl::size_t<0>, width_of<OpT> >));
            typedef static_xpression<simple_repeat_matcher<OpT, GreedyT>, StateT> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &, uint_t min = MinT, uint_t max = MaxT)
        {
            return make_static_xpression(simple_repeat_matcher<OpT, GreedyT>(op, min, max), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // plus_transform
    //   Optimization: don't insert a hidden mark if we already have a visible one
    template<bool GreedyT = true, uint_t MinT = 1, uint_t MaxT = UINT_MAX-1>
    struct plus_transform
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename mpl::if_
            <
                is_marker<typename proto::arg_type<OpT>::type>
              , plus_no_mark_transform<GreedyT, MinT, MaxT>
              , plus_mark_transform<GreedyT, MinT, MaxT>
            >::type transform;

            typedef typename transform::BOOST_NESTED_TEMPLATE apply<OpT, StateT, VisitorT>::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor, uint_t min = MinT, uint_t max = MaxT)
        {
            return apply<OpT, StateT, VisitorT>::transform::call(op, state, visitor, mark_number(proto::arg(op), visitor), min, max);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // star_transform
    template<bool GreedyT = true, uint_t MaxT = UINT_MAX-1>
    struct star_transform
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename plus_transform<GreedyT, 1, MaxT>::BOOST_NESTED_TEMPLATE apply
            <
                OpT
              , StateT
              , VisitorT
            >::type plus_type;

            typedef typename optional_transform<GreedyT>::BOOST_NESTED_TEMPLATE apply
            <
                proto::unary_op<plus_type, proto::unary_plus_tag>
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor, uint_t max = MaxT)
        {
            return optional_transform<GreedyT>::call
            (
                +plus_transform<GreedyT, 1, MaxT>::call(op, state, visitor, 1, max)
              , state
              , visitor
            );
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // epsilon_transform
    struct epsilon_transform
    {
        template<typename, typename, typename>
        struct apply
        {
            typedef proto::unary_op<epsilon_matcher, proto::noop_tag> type;
        };

        static proto::unary_op<epsilon_matcher, proto::noop_tag> 
        call(dont_care, dont_care, dont_care)
        {
            return proto::noop(epsilon_matcher());
        }
    };

}}}

#endif
