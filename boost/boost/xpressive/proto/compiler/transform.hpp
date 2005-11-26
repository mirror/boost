///////////////////////////////////////////////////////////////////////////////
// transform.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_TRANSFORM_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILER_TRANSFORM_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/arg_traits.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // transform_compiler
    //   accepts a transformation as a lambda, applies the transformation to any
    //   parse tree passed in, and then compiles the result using the specified
    //   compiler
    template<typename LambdaT, typename DomainTagT, typename CompilerT>
    struct transform_compiler
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename CompilerT::BOOST_NESTED_TEMPLATE apply
            <
                typename LambdaT::BOOST_NESTED_TEMPLATE apply<OpT, StateT, VisitorT>::type
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return CompilerT::call(LambdaT::call(op, state, visitor), state, visitor);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // if no compiler is specified, the transform_compiler forwards to the default
    // compiler
    template<typename LambdaT, typename DomainTagT>
    struct transform_compiler<LambdaT, DomainTagT, void>
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename LambdaT::BOOST_NESTED_TEMPLATE apply
            <
                OpT
              , StateT
              , VisitorT
            >::type trans_type;

            typedef proto::compiler<typename tag_type<trans_type>::type, DomainTagT> compiler_type;

            typedef typename compiler_type::BOOST_NESTED_TEMPLATE apply
            <
                trans_type
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return proto::compile(LambdaT::call(op, state, visitor), state, visitor, DomainTagT());
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // arg_transform
    struct arg_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            typedef typename arg_type<OpT>::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename arg_type<OpT>::const_reference
        call(OpT const &op, StateT const &, VisitorT &)
        {
            return proto::arg(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // left_transform
    struct left_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            typedef typename left_type<OpT>::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename left_type<OpT>::const_reference
        call(OpT const &op, StateT const &, VisitorT &)
        {
            return proto::left(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // right_transform
    struct right_transform
    {
        template<typename OpT, typename, typename>
        struct apply
        {
            typedef typename right_type<OpT>::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename right_type<OpT>::const_reference
        call(OpT const &op, StateT const &, VisitorT &)
        {
            return proto::right(op);
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // compose_transforms
    //   execute two transforms in succession
    template<typename FirstT, typename SecondT>
    struct compose_transforms
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename SecondT::BOOST_NESTED_TEMPLATE apply
            <
                typename FirstT::BOOST_NESTED_TEMPLATE apply<OpT, StateT, VisitorT>::type
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return SecondT::call(FirstT::call(op, state, visitor), state, visitor);
        }
    };

}}

#endif
