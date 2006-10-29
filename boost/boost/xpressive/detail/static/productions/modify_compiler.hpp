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
    template<typename Old, typename New>
    struct scoped_swap
    {
        ~scoped_swap() { this->old_->swap(*this->new_); }
        Old *old_;
        New *new_;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // modify_compiler
    struct modify_compiler
    {
        template<typename Expr, typename State, typename Visitor>
        struct apply
        {
            typedef typename Expr::arg0_type modifier_type;
            typedef typename Expr::arg1_type expr_type;
            typedef typename modifier_type::BOOST_NESTED_TEMPLATE apply<Visitor>::type visitor_type;

            typedef typename proto::compiler<typename expr_type::tag_type, seq_tag>::
                BOOST_NESTED_TEMPLATE apply
            <
                expr_type
              , State
              , visitor_type
            >::type type;
        };

        template<typename Expr, typename State, typename Visitor>
        static typename apply<Expr, State, Visitor>::type
        call(Expr const &expr, State const &state, Visitor &visitor)
        {
            typedef typename apply<Expr, State, Visitor>::visitor_type new_visitor_type;
            new_visitor_type new_visitor(proto::left(expr).call(visitor));
            new_visitor.swap(visitor);
            scoped_swap<Visitor, new_visitor_type> const undo = {&visitor, &new_visitor};
            detail::ignore_unused(undo);
            return proto::compile(proto::right(expr), state, new_visitor, seq_tag());
        }
    };

}}}

namespace boost { namespace proto
{

    // production for modifiers
    template<>
    struct compiler<xpressive::detail::modifier_tag, xpressive::detail::seq_tag, void>
      : xpressive::detail::modify_compiler
    {
    };

}}

#endif
