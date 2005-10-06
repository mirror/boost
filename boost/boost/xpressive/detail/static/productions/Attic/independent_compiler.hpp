///////////////////////////////////////////////////////////////////////////////
// independent_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_INDEPENDENT_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_INDEPENDENT_COMPILER_HPP_EAN_10_04_2005

#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{
    template<bool PositiveT>
    struct lookahead_tag : proto::unary_tag {};

    template<bool PositiveT>
    struct lookbehind_tag : proto::unary_tag {};

    struct keeper_tag : proto::unary_tag {};

    ///////////////////////////////////////////////////////////////////////////////
    // lookahead_branch
    template<bool PositiveT>
    struct lookahead_branch
    {
        typedef true_xpression state_type;

        template<typename OpT, typename StateT, typename>
        struct apply
        {
            typedef static_xpression<lookahead_matcher<OpT>, StateT> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static static_xpression<lookahead_matcher<OpT>, StateT>
        call(OpT const &op, StateT const &state, VisitorT &)
        {
            return make_static_xpression(lookahead_matcher<OpT>(op, !PositiveT), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // lookbehind_branch
    template<bool PositiveT>
    struct lookbehind_branch
    {
        typedef true_xpression state_type;

        template<typename OpT, typename StateT, typename>
        struct apply
        {
            typedef static_xpression<lookbehind_matcher<OpT>, StateT> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static static_xpression<lookbehind_matcher<OpT>, StateT>
        call(OpT const &op, StateT const &state, VisitorT &)
        {
            return make_static_xpression(lookbehind_matcher<OpT>(op, !PositiveT), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // keeper_branch
    struct keeper_branch
    {
        typedef true_xpression state_type;

        template<typename OpT, typename StateT, typename>
        struct apply
        {
            typedef static_xpression<keeper_matcher<OpT>, StateT> type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static static_xpression<keeper_matcher<OpT>, StateT>
        call(OpT const &op, StateT const &state, VisitorT &)
        {
            return make_static_xpression(keeper_matcher<OpT>(op), state);
        }
    };

}}}


namespace boost { namespace proto {

    template<bool PositiveT>
    struct compiler<xpressive::detail::lookahead_tag<PositiveT>, xpressive::detail::seq_tag>
      : branch_compiler<xpressive::detail::lookahead_branch<PositiveT>, xpressive::detail::ind_tag>
    {
    };

    template<bool PositiveT>
    struct compiler<xpressive::detail::lookbehind_tag<PositiveT>, xpressive::detail::seq_tag>
      : branch_compiler<xpressive::detail::lookbehind_branch<PositiveT>, xpressive::detail::ind_tag>
    {
    };

    template<>
    struct compiler<xpressive::detail::keeper_tag, xpressive::detail::seq_tag>
      : branch_compiler<xpressive::detail::keeper_branch, xpressive::detail::ind_tag>
    {
    };
    
    template<typename OpTagT>
    struct compiler<OpTagT, xpressive::detail::ind_tag>
      : transform_compiler<arg_transform, xpressive::detail::seq_tag>
    {
    };

}}


#endif
