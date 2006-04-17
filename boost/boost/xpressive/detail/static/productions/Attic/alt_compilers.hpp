///////////////////////////////////////////////////////////////////////////////
// alt_compilers.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_ALT_COMPILERS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_ALT_COMPILERS_HPP_EAN_10_04_2005

#include <boost/version.hpp>
#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/compiler/fold.hpp>
#include <boost/xpressive/proto/compiler/branch.hpp>
#include <boost/xpressive/detail/utility/cons.hpp>
#include <boost/xpressive/detail/utility/dont_care.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // alternates_list
    //   a fusion-compatible sequence of alternate expressions, that also keeps
    //   track of the list's width and purity.
    template<typename Head, typename Tail>
    struct alternates_list
      : fusion::cons<Head, Tail>
    {
        BOOST_STATIC_CONSTANT(std::size_t, width = Head::width == Tail::width ? Head::width : unknown_width::value);
        BOOST_STATIC_CONSTANT(bool, pure = Head::pure && Tail::pure);

        alternates_list(Head const &head, Tail const &tail)
          : fusion::cons<Head, Tail>(head, tail)
        {
        }
    };

    template<typename Head>
    struct alternates_list<Head, fusion::nil>
      : fusion::cons<Head, fusion::nil>
    {
        BOOST_STATIC_CONSTANT(std::size_t, width = Head::width);
        BOOST_STATIC_CONSTANT(bool, pure = Head::pure);

        alternates_list(Head const &head, fusion::nil const &tail)
          : fusion::cons<Head, fusion::nil>(head, tail)
        {
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // alt_branch
    //   Describes how to construct an alternate xpression
    struct alt_branch
    {
        typedef fusion::nil state_type;

        template<typename Op, typename State, typename Visitor>
        struct apply
        {
            typedef static_xpression
            <
                alternate_matcher<Op, typename Visitor::traits_type>
              , State
            > type;
        };

        template<typename Op, typename State, typename Visitor>
        static typename apply<Op, State, Visitor>::type
        call(Op const &op, State const &state, Visitor &)
        {
            typedef typename Visitor::traits_type traits_type;
            return make_static(alternate_matcher<Op, traits_type>(op), state);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // alt_list_branch
    struct alt_list_branch
    {
        typedef alternate_end_xpression state_type;

        template<typename Op, typename State, typename>
        struct apply
        {
            typedef alternates_list<Op, State> type;
        };

        template<typename Op, typename State>
        static alternates_list<Op, State>
        call(Op const &op, State const &state, dont_care)
        {
            return alternates_list<Op, State>(op, state);
        }
    };

}}}

namespace boost { namespace proto
{
    // production for alternates in sequence
    template<>
    struct compiler<bitor_tag, xpressive::detail::seq_tag, void>
      : branch_compiler<xpressive::detail::alt_branch, xpressive::detail::alt_tag>
    {
    };

    // handle alternates with the alt branch compiler
    template<typename OpTag>
    struct compiler<OpTag, xpressive::detail::alt_tag, void>
      : branch_compiler<xpressive::detail::alt_list_branch, xpressive::detail::seq_tag>
    {
    };

    // production for alternates in alternate
    template<>
    struct compiler<bitor_tag, xpressive::detail::alt_tag, void>
      : fold_compiler<bitor_tag, xpressive::detail::alt_tag>
    {
    };

}}

#endif
