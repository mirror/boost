///////////////////////////////////////////////////////////////////////////////
// proto.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_HPP_EAN_04_01_2005
#define BOOST_PROTO_HPP_EAN_04_01_2005

#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/op_tags.hpp>
#include <boost/xpressive/proto/op_base.hpp>
#include <boost/xpressive/proto/operators.hpp>
#include <boost/xpressive/proto/arg_traits.hpp>

namespace boost { namespace proto
{
    ///////////////////////////////////////////////////////////////////////////////
    // compile
    template<typename OpT, typename StateT, typename VisitorT, typename DomainTagT>
    typename lazy_enable_if<
        is_op<OpT>
      , typename compiler<typename tag_type<OpT>::type, DomainTagT>::BOOST_NESTED_TEMPLATE apply
        <
            OpT
          , StateT
          , VisitorT
        >
    >::type const
    compile(OpT const &op, StateT const &state, VisitorT &visitor, DomainTagT)
    {
        typedef compiler<typename tag_type<OpT>::type, DomainTagT> compiler;
        return compiler::call(as_op<OpT>::make(op), state, visitor);
    }

}} // namespace boost::proto

#endif
