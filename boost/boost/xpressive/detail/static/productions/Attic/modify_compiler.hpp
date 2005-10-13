///////////////////////////////////////////////////////////////////////////////
// modify_compiler.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MODIFY_COMPILER_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_PRODUCTIONS_MODIFY_COMPILER_HPP_EAN_10_04_2005

#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/detail/utility/ignore_unused.hpp>

namespace boost { namespace xpressive { namespace detail
{

    ///////////////////////////////////////////////////////////////////////////////
    // regex operator tags
    struct modifier_tag
      : proto::binary_tag
    {
    };

    ///////////////////////////////////////////////////////////////////////////////
    // scoped_swap
    //  for swapping state back after proto::compile returns
    template<typename OldT, typename NewT>
    struct scoped_swap
    {
        ~scoped_swap() { this->old_->swap(*this->new_); }
        OldT *old_;
        NewT *new_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // modify_compiler
    struct modify_compiler
    {
        template<typename OpT, typename StateT, typename VisitorT>
        struct apply
        {
            typedef typename proto::left_type<OpT>::type modifier_type;
            typedef typename modifier_type::BOOST_NESTED_TEMPLATE apply<VisitorT>::type visitor_type;
            typedef typename proto::right_type<OpT>::type op_type;

            typedef typename proto::compiler<typename proto::tag_type<op_type>::type, seq_tag>::
                BOOST_NESTED_TEMPLATE apply
            <
                op_type
              , StateT
              , visitor_type
            >::type type;
        };

        template<typename OpT, typename StateT, typename VisitorT>
        static typename apply<OpT, StateT, VisitorT>::type
        call(OpT const &op, StateT const &state, VisitorT &visitor)
        {
            typedef typename apply<OpT, StateT, VisitorT>::visitor_type new_visitor_type;
            new_visitor_type new_visitor(proto::left(op).call(visitor));
            new_visitor.swap(visitor);
            scoped_swap<VisitorT, new_visitor_type> const undo = {&visitor, &new_visitor};
            detail::ignore_unused(&undo);
            return proto::compile(proto::right(op), state, new_visitor, seq_tag());
        }
    };

}}}

namespace boost { namespace proto
{

    // production for modifiers
    template<>
    struct compiler<xpressive::detail::modifier_tag, xpressive::detail::seq_tag>
      : xpressive::detail::modify_compiler
    {
    };

}}

#endif
