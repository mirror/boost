///////////////////////////////////////////////////////////////////////////////
// branch.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_BRANCH_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILER_BRANCH_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // branch_compiler
    template<typename LambdaT, typename DomainTagT>
    struct branch_compiler
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef proto::compiler<typename tag_type<OpT>::type, DomainTagT> compiler_type;

            // Compile the branch
            typedef typename compiler_type::BOOST_NESTED_TEMPLATE apply
             <
                OpT
              , typename LambdaT::state_type
              , VisitorT
            >::type branch_type;

            // Pass the branch, state and visitor to the lambda
            typedef typename LambdaT::BOOST_NESTED_TEMPLATE apply
            <
                branch_type
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            return LambdaT::call
            (
                proto::compile(op, typename LambdaT::state_type(), visitor, DomainTagT())
              , state
              , visitor
            );
        }
    };

}}

#endif
