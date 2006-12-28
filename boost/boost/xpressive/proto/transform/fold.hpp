///////////////////////////////////////////////////////////////////////////////
/// \file fold.hpp
/// A special-purpose proto transform for merging sequences of binary operations.
/// It transforms the right operand and passes the result as state while transforming
/// the left. Or, it might do the left first, if you choose.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_12_16_2006
#define BOOST_PROTO_TRANSFORM_FOLD_HPP_EAN_12_16_2006

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>

namespace boost { namespace proto { namespace transform
{

    // A fold transform that transforms the left sub-tree and
    // uses the result as state while transforming the right.
    template<typename Grammar>
    struct fold
      : Grammar
    {
        fold();

        typedef typename Grammar::type grammar_type;
        typedef typename grammar_type::arg0_type left_grammar;
        typedef typename grammar_type::arg1_type right_grammar;

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::meta::left<Expr>::type left_expr;
            typedef typename proto::meta::right<Expr>::type right_expr;

            typedef typename right_grammar::template apply<
                right_expr
              , typename left_grammar::template apply<left_expr, State, Visitor>::type
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return right_grammar::call(
                proto::right(expr)
              , left_grammar::call(proto::left(expr), state, visitor)
              , visitor
            );
        }
    };

    // A reverse_fold compiler that compiles the right sub-tree and
    // uses the result as state while compiling the left.
    template<typename Grammar>
    struct reverse_fold
      : Grammar
    {
        reverse_fold();

        typedef typename Grammar::type grammar_type;
        typedef typename grammar_type::arg0_type left_grammar;
        typedef typename grammar_type::arg1_type right_grammar;

        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename proto::meta::left<Expr>::type left_expr;
            typedef typename proto::meta::right<Expr>::type right_expr;

            typedef typename left_grammar::template apply<
                left_expr
              , typename right_grammar::template apply<right_expr, State, Visitor>::type
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return left_grammar::call(
                proto::left(expr)
              , right_grammar::call(proto::right(expr), state, visitor)
              , visitor
            );
        }
    };

}}}

#endif
