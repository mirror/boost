///////////////////////////////////////////////////////////////////////////////
// noop_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_NOOP_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_NOOP_COMPILER_HPP_EAN_10_04_2005

#include <boost/xpressive/detail/detail_fwd.hpp>
#include <boost/xpressive/detail/static/productions/independent_compiler.hpp>
#include <boost/xpressive/detail/static/productions/domain_tags.hpp>

namespace boost { namespace xpressive { namespace detail
{
    ///////////////////////////////////////////////////////////////////////////////
    // regex compiler productions
    struct terminal_compiler
    {
        ///////////////////////////////////////////////////////////////////////////////
        // transformation that happens to leaf nodes in the parse tree
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef static_xpression<
                typename Visitor::BOOST_NESTED_TEMPLATE apply<
                    typename proto::result_of::arg<Expr>::type
                >::type
              , State
            > type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return make_static(visitor.call(proto::arg(expr)), state);
        }
    };

}}}

namespace boost { namespace proto
{

    // production for terminals in sequence
    template<>
    struct compiler<tag::terminal, xpressive::detail::seq_tag, void>
      : xpressive::detail::terminal_compiler
    {
    };

}}

#endif
