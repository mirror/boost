///////////////////////////////////////////////////////////////////////////////
// switch.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_COMPILER_SWITCH_HPP_EAN_04_01_2005
#define BOOST_PROTO_COMPILER_SWITCH_HPP_EAN_04_01_2005

#include <boost/mpl/at.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto
{

    ///////////////////////////////////////////////////////////////////////////////
    // switch_compiler
    //  applies a transform, then looks up the appropriate compiler in a map
    template<typename LambdaT, typename MapT>
    struct switch_compiler
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename boost::mpl::at
            <
                MapT
              , typename LambdaT::BOOST_NESTED_TEMPLATE apply<OpT, StateT, VisitorT>::type
            >::type compiler_type;
            
            typedef typename compiler_type::BOOST_NESTED_TEMPLATE apply
            <
                OpT
              , StateT
              , VisitorT
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            typedef typename apply<OpT, StateT, VisitorT>::compiler_type compiler_type;
            return compiler_type::call(op, state, visitor);
        }
    };

}}

#endif
