///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Proto transforms for extracting arguments from expressions.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_12_16_2006
#define BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_12_16_2006

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>

namespace boost { namespace proto { namespace transform
{

    // A compiler that simply extracts the arg from an expression
    template<typename Grammar, typename N>
    struct arg
      : Grammar
    {
        arg();

        template<typename Expr, typename, typename>
        struct apply
          : proto::meta::arg<Expr, N>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::arg<N>(expr);
        }
    };

    // A compiler that simply extracts the arg from an expression
    template<typename Grammar, long N>
    struct arg_c
      : Grammar
    {
        arg_c();

        template<typename Expr, typename, typename>
        struct apply
          : proto::meta::arg_c<Expr, N>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::arg_c<N>(expr);
        }
    };

    // A compiler that simply extracts the left arg from an expression
    template<typename Grammar>
    struct left
      : Grammar
    {
        left();

        template<typename Expr, typename, typename>
        struct apply
          : proto::meta::left<Expr>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::left(expr);
        }
    };

    // A compiler that simply extracts the right arg from an expression
    template<typename Grammar>
    struct right
      : Grammar
    {
        right();

        template<typename Expr, typename, typename>
        struct apply
          : proto::meta::right<Expr>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::right(expr);
        }
    };

}}}

#endif
