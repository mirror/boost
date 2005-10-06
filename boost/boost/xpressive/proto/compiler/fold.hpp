///////////////////////////////////////////////////////////////////////////////
// fold.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_FOLD_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILER_FOLD_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // fold_compiler
    //  Compiles the right side and passes the result as state while compiling the left.
    //  This is useful for serializing a tree.
    template<typename OpTagT, typename DomainTagT, bool RightFirstT>
    struct fold_compiler
    {
        // sample compiler implementation for sequencing
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename right_type<OpT>::type right_type;
            typedef typename left_type<OpT>::type left_type;

            // compile the right branch
            typedef typename compiler<typename tag_type<right_type>::type, DomainTagT>::
                BOOST_NESTED_TEMPLATE apply
            <
                right_type
              , StateT
              , VisitorT
            >::type right_compiled_type;

            // forward the result of the right branch to the left
            typedef typename compiler<typename tag_type<left_type>::type, DomainTagT>::
                BOOST_NESTED_TEMPLATE apply
            <
                left_type
              , right_compiled_type
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return proto::compile(
                proto::left(op)
              , proto::compile(proto::right(op), state, visitor, DomainTagT())
              , visitor
              , DomainTagT()
            );
        }
    };

    ///////////////////////////////////////////////////////////////////////////////
    // fold_compiler
    //  Compiles the left side and passes the result as state while compiling the right.
    //  This is useful for serializing a tree.
    template<typename OpTagT, typename DomainTagT>
    struct fold_compiler<OpTagT, DomainTagT, false>
    {
        // sample compiler implementation for sequencing
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename right_type<OpT>::type right_type;
            typedef typename left_type<OpT>::type left_type;

            // compile the right branch
            typedef typename compiler<typename tag_type<left_type>::type, DomainTagT>::
                BOOST_NESTED_TEMPLATE apply
            <
                left_type
              , StateT
              , VisitorT
            >::type left_compiled_type;

            // forward the result of the right branch to the left
            typedef typename compiler<typename tag_type<right_type>::type, DomainTagT>::
                BOOST_NESTED_TEMPLATE apply
            <
                right_type
              , left_compiled_type
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return proto::compile(
                proto::right(op)
              , proto::compile(proto::left(op), state, visitor, DomainTagT())
              , visitor
              , DomainTagT()
            );
        }
    };

}}

#endif
