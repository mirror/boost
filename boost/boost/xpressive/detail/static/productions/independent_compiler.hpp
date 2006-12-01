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
    template<bool Positive>
    struct lookahead_tag : proto::tag::unary {};

    template<bool Positive>
    struct lookbehind_tag : proto::tag::unary {};

    struct keeper_tag : proto::tag::unary {};

    ///////////////////////////////////////////////////////////////////////////////
    // lookahead_branch
    template<bool Positive>
    struct lookahead_branch
    {
        typedef true_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<lookahead_matcher<Expr>, State> type;
        };

        template<typename Expr, typename State, typename Visitor>
        static static_xpression<lookahead_matcher<Expr>, State>
        call(Expr const &expr, State const &state, Visitor &)
        {
            return make_static(lookahead_matcher<Expr>(expr, !Positive), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // lookbehind_branch
    template<bool Positive>
    struct lookbehind_branch
    {
        typedef true_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<lookbehind_matcher<Expr>, State> type;
        };

        template<typename Expr, typename State, typename Visitor>
        static static_xpression<lookbehind_matcher<Expr>, State>
        call(Expr const &expr, State const &state, Visitor &)
        {
            std::size_t width = expr.get_width().value();
            return make_static(lookbehind_matcher<Expr>(expr, width, !Positive), state);
        }
    };

    struct keeper_branch
    {
        typedef true_xpression state_type;

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<keeper_matcher<Expr>, State> type;
        };

        template<typename Expr, typename State, typename Visitor>
        static static_xpression<keeper_matcher<Expr>, State>
        call(Expr const &expr, State const &state, Visitor &)
        {
            return make_static(keeper_matcher<Expr>(expr), state);
        }
    };

}}}


namespace boost { namespace proto
{

    template<bool Positive>
    struct compiler<xpressive::detail::lookahead_tag<Positive>, xpressive::detail::seq_tag, void>
      : branch_compiler<xpressive::detail::lookahead_branch<Positive>, xpressive::detail::ind_tag>
    {
    };

    template<bool Positive>
    struct compiler<xpressive::detail::lookbehind_tag<Positive>, xpressive::detail::seq_tag, void>
      : branch_compiler<xpressive::detail::lookbehind_branch<Positive>, xpressive::detail::ind_tag>
    {
    };

    template<>
    struct compiler<xpressive::detail::keeper_tag, xpressive::detail::seq_tag, void>
      : branch_compiler<xpressive::detail::keeper_branch, xpressive::detail::ind_tag>
    {
    };

    template<typename OpTag>
    struct compiler<OpTag, xpressive::detail::ind_tag, void>
      : transform_compiler<arg_transform, xpressive::detail::seq_tag>
    {
    };

}}


#endif
