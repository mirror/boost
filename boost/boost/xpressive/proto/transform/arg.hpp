///////////////////////////////////////////////////////////////////////////////
/// \file arg.hpp
/// Proto transforms for extracting arguments from expressions.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_12_16_2006
#define BOOST_PROTO_TRANSFORM_ARG_HPP_EAN_12_16_2006

#if !defined(__WAVE__) || !defined(BOOST_PROTO_DOXYGEN_INVOKED)
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>
#else
/// INTERNAL ONLY
/// Needed to work around doxygen bug
struct a_dummy_global;
#endif

namespace boost { namespace proto { namespace transform
{

    // A transform that simply extracts the arg from an expression
    template<typename Grammar, typename N>
    struct arg
      : Grammar
    {
        arg();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::meta::arg<typename Grammar::template apply<Expr, State, Visitor>::type, N>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type //reference
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            // BUGBUG Grammar::call could return a temporary!
            // Don't return a dangling reference
            return proto::arg<N>(Grammar::call(expr, state, visitor));
        }
    };

    // A transform that simply extracts the arg from an expression
    template<typename Grammar, long N>
    struct arg_c
      : Grammar
    {
        arg_c();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::meta::arg_c<typename Grammar::template apply<Expr, State, Visitor>::type, N>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type //const &
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return proto::arg_c<N>(Grammar::call(expr, state, visitor));
        }
    };

    // A transform that simply extracts the left arg from an expression
    template<typename Grammar>
    struct left
      : Grammar
    {
        left();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::meta::left<typename Grammar::template apply<Expr, State, Visitor>::type>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type //const &
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return proto::left(Grammar::call(expr, state, visitor));
        }
    };

    // A transform that simply extracts the right arg from an expression
    template<typename Grammar>
    struct right
      : Grammar
    {
        right();

        template<typename Expr, typename State, typename Visitor>
        struct apply
          : proto::meta::right<typename Grammar::template apply<Expr, State, Visitor>::type>
        {};

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type //const &
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return proto::right(Grammar::call(expr, state, visitor));
        }
    };

    // Just return the state
    template<typename Grammar>
    struct state
      : Grammar
    {
        state();

        template<typename, typename State, typename>
        struct apply
        {
            typedef State type;
        };

        template<typename Expr, typename State, typename Visitor>
        static State const &
        call(Expr const &, State const &state_, Visitor &)
        {
            return state_;
        }
    };

    // Just return the visitor
    template<typename Grammar>
    struct visitor
      : Grammar
    {
        visitor();

        template<typename, typename, typename Visitor>
        struct apply
        {
            typedef Visitor type;
        };

        template<typename Expr, typename State, typename Visitor>
        static Visitor &
        call(Expr const &, State const &, Visitor &visitor_)
        {
            return visitor_;
        }
    };

    // Always return the specified type/object
    template<typename Grammar, typename Always, Always const &Value>
    struct always
      : Grammar
    {
        always();

        template<typename, typename, typename>
        struct apply
        {
            typedef Always type;
        };

        template<typename Expr, typename State, typename Visitor>
        static Always const &
        call(Expr const &, State const &, Visitor &)
        {
            return Value;
        }
    };

    // Just return the passed in Expr
    template<typename Grammar>
    struct identity
      : Grammar
    {
        identity();
        BOOST_PROTO_IDENTITY_TRANSFORM();
    };

}}}

#endif
