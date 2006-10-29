///////////////////////////////////////////////////////////////////////////////
/// \file transform.hpp
/// A special-purpose proto compiler for applying a transformation to an
/// expression. The transformation is a proto lambda. The result of the
/// transformation is forwarded to the specified compiler, or to the
/// default compiler for the resulting expression is no compiler is
/// specified. Also included are some basic transforms, such as one that
/// extracts the operand of a unary expr, the left and right operands of
/// a binary expr, and a way to compose multiple transforms into one.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_TRANSFORM_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILER_TRANSFORM_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/traits.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // transform_compiler
    //   accepts a transformation as a lambda, applies the transformation to any
    //   parse tree passed in, and then compiles the result using the specified
    //   compiler
    template<typename Lambda, typename DomainTag, typename Compiler>
    struct transform_compiler
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename Compiler::BOOST_NESTED_TEMPLATE apply
            <
                typename Lambda::BOOST_NESTED_TEMPLATE apply<Expr, State, Visitor>::type
              , State
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return Compiler::call(Lambda::call(expr, state, visitor), state, visitor);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // if no compiler is specified, the transform_compiler forwards to the default
    // compiler
    template<typename Lambda, typename DomainTag>
    struct transform_compiler<Lambda, DomainTag, void>
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename Lambda::BOOST_NESTED_TEMPLATE apply
            <
                Expr
              , State
              , Visitor
            >::type trans_type;

            typedef proto::compiler<typename trans_type::tag_type, DomainTag> compiler_type;

            typedef typename compiler_type::BOOST_NESTED_TEMPLATE apply
            <
                trans_type
              , State
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            //typename apply<Expr, State, Visitor>::trans_type trans = Lambda::call(expr, state, visitor);
            //return proto::compile(trans, state, visitor, DomainTag());
            return proto::compile(Lambda::call(expr, state, visitor), state, visitor, DomainTag());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // identity_transform
    //   pass through without doing a transform
    struct identity_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef Expr type;
        };

        template<typename Expr, typename State, typename Visitor>
        static Expr const &call(Expr const &expr, State const &, Visitor &)
        {
            return expr;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // arg_transform
    struct arg_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename Expr::arg0_type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::arg(expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // left_transform
    struct left_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename Expr::arg0_type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::left(expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // right_transform
    struct right_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename Expr::arg1_type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            return proto::right(expr);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // unary_op_transform
    //   insert a unary operation
    template<typename Tag>
    struct unary_op_transform
    {
        template<typename Expr, typename, typename>
        struct apply
        {
            typedef typename meta::unary_expr<Tag, Expr>::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename meta::unary_expr<Tag, Expr>::type
        call(Expr const &expr, State const &, Visitor &)
        {
            typename meta::unary_expr<Tag, Expr>::type that = {expr};
            return that;
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // compose_transforms
    //   execute two transforms in succession
    template<typename First, typename Second>
    struct compose_transforms
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename Second::BOOST_NESTED_TEMPLATE apply
            <
                typename First::BOOST_NESTED_TEMPLATE apply<Expr, State, Visitor>::type
              , State
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return Second::call(First::call(expr, state, visitor), state, visitor);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // conditional_transform
    //   Conditionally execute a transform
    template<typename Predicate, typename IfTransform, typename ElseTransform>
    struct conditional_transform
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename boost::mpl::if_
            <
                typename Predicate::BOOST_NESTED_TEMPLATE apply<Expr, State, Visitor>::type
              , IfTransform
              , ElseTransform
            >::type transform_type;

            typedef typename transform_type::BOOST_NESTED_TEMPLATE apply
            <
                Expr
              , State
              , Visitor
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            return apply<Expr, State, Visitor>::transform_type::call(expr, state, visitor);
        }
    };

    template<typename Always>
    struct always_transform
    {
        template<typename, typename, typename>
        struct apply
        {
            typedef Always type;
        };

        template<typename Expr, typename State, typename Visitor>
        static Always
        call(Expr const &, State const &, Visitor &)
        {
            return Always();
        }
    };

}}

#endif
