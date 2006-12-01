////////////////////////////////////////////////////////////////////////////
// set_compilers.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_SET_COMPILERS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_SET_COMPILERS_HPP_EAN_10_04_2005

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/fold.hpp>
#include <boost/xpressive/proto/compiler/branch.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/utility/traits_utils.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // set_branch
    //
    struct set_branch
    {
        typedef no_next state_type;

        template<typename, typename State, typename>
        struct apply
        {
            typedef State type;
        };

        template<typename Expr, typename State, typename Visitor>
        static State const &call(Expr const &expr, State const &state, Visitor &)
        {
            return state.set(set_branch::get_matcher(expr)), state;
        }

    private:

        template<typename Matcher>
        static Matcher const &get_matcher(static_xpression<Matcher, no_next> const &xpr)
        {
            return xpr;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // list_branch
    struct list_branch
    {
        typedef int state_type; // not used

        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef static_xpression<Expr, State> type;
        };

        template<typename Expr, typename State>
        static static_xpression<Expr, State>
        call(Expr const &expr, State const &state, dont_care)
        {
            return make_static(expr, state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // list_terminal_compiler
    struct list_terminal_compiler
    {
        template<typename, typename State, typename>
        struct apply
        {
            typedef typename State::next_type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename State::next_type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef typename Visitor::char_type char_type;
            char_type ch = char_cast<char_type>(proto::arg(expr), visitor.traits());
            return state.push_back(ch, visitor.traits());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // list_assign_compiler
    struct list_assign_compiler
    {
        template<typename Expr, typename, typename Visitor>
        struct apply
        {
            typedef typename Visitor::traits_type traits_type;
            typedef set_matcher<traits_type, 1> type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &visitor)
        {
            typedef typename Visitor::char_type char_type;
            char_type ch = char_cast<char_type>(proto::arg(proto::right(expr)), visitor.traits());
            return typename apply<Expr, State, Visitor>::type(ch, visitor.traits());
        }
    };

}}}

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // compilers for sets such as set['a' | range('a','z')]
    template<>
    struct compiler<tag::bitwise_or, xpressive::detail::set_tag, void>
      : reverse_fold_compiler<xpressive::detail::set_tag>
    {
    };

    template<>
    struct compiler<tag::terminal, xpressive::detail::set_tag, void>
      : branch_compiler<xpressive::detail::set_branch, xpressive::detail::seq_tag>
    {
    };

    template<>
    struct compiler<tag::complement, xpressive::detail::set_tag, void>
      : branch_compiler<xpressive::detail::set_branch, xpressive::detail::seq_tag>
    {
    };

    template<>
    struct compiler<tag::comma, xpressive::detail::set_tag, void>
      : branch_compiler<xpressive::detail::set_branch, xpressive::detail::seq_tag>
    {
    };


    ///////////////////////////////////////////////////////////////////////////////
    // compilers for list-initialized sets such as (set='a','b','c')
    template<>
    struct compiler<tag::comma, xpressive::detail::seq_tag, void>
      : branch_compiler<xpressive::detail::list_branch, xpressive::detail::lst_tag>
    {
    };

    template<>
    struct compiler<tag::comma, xpressive::detail::lst_tag, void>
      : fold_compiler<xpressive::detail::lst_tag>
    {
    };

    template<>
    struct compiler<tag::terminal, xpressive::detail::lst_tag, void>
      : xpressive::detail::list_terminal_compiler
    {
    };

    template<>
    struct compiler<tag::assign, xpressive::detail::lst_tag, void>
      : xpressive::detail::list_assign_compiler
    {
    };

}}

#endif
