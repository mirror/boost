///////////////////////////////////////////////////////////////////////////////
/// \file list.hpp
/// A special-purpose proto compiler for putting things into a
/// fusion::cons<> list.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_LIST_HPP_EAN_12_12_2006
#define BOOST_PROTO_COMPILER_LIST_HPP_EAN_12_12_2006

#include <boost/fusion/sequence/container/list/cons.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // list_compiler
    //  Use Expr as the head of a fusion cons-list, and state as the tail.
    struct list_compiler
    {
        template<typename Expr, typename State, typename>
        struct apply
        {
            typedef fusion::cons<Expr, State> type;
        };

        template<typename Expr, typename State, typename Visitor>
        static fusion::cons<Expr, State> const
        call(Expr const &expr, State const &state, Visitor &)
        {
            return fusion::cons<Expr, State>(expr, state);
        }
    };

}}

#endif
