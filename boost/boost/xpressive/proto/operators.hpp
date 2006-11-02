///////////////////////////////////////////////////////////////////////////////
/// \file operators.hpp
/// Contains all the overloaded operators that make it possible to build
/// expression templates using proto components
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OPERATORS_HPP_EAN_04_01_2005
#define BOOST_PROTO_OPERATORS_HPP_EAN_04_01_2005

#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/basic_expr.hpp>

namespace boost { namespace proto
{
#define BOOST_PROTO_UNARY_OP(op, tag)\
    template<typename Tag, typename Args, long Arity>\
    inline basic_expr<tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > const\
    operator op(basic_expr<Tag, Args, Arity> const &arg)\
    {\
        basic_expr<tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > that = {{arg}};\
        return that;\
    }\
    /**/

#define BOOST_PROTO_BINARY_OP(op, tag)\
    template<typename LTag, typename LArgs, long LArity, typename Right>\
    inline basic_expr<tag, mpl::vector2<ref<basic_expr<LTag, LArgs, LArity> >, typename meta::terminal<Right>::type> > const\
    operator op(basic_expr<LTag, LArgs, LArity> const &left, Right const &right)\
    {\
        basic_expr<tag, mpl::vector2<ref<basic_expr<LTag, LArgs, LArity> >, typename meta::terminal<Right>::type> > that = {{left}, proto::make_terminal(right)};\
        return that;\
    }\
    template<typename Left, typename RTag, typename RArgs, long RArity>\
    inline basic_expr<tag, mpl::vector2<typename meta::terminal<Left>::type, ref<basic_expr<RTag, RArgs, RArity> > > > const\
    operator op(Left const &left, basic_expr<RTag, RArgs, RArity> const &right)\
    {\
        basic_expr<tag, mpl::vector2<typename meta::terminal<Left>::type, ref<basic_expr<RTag, RArgs, RArity> > > > that = {proto::make_terminal(left), {right}};\
        return that;\
    }\
    template<typename LTag, typename LArgs, long LArity, typename RTag, typename RArgs, long RArity>\
    inline basic_expr<tag, mpl::vector2<ref<basic_expr<LTag, LArgs, LArity> >, ref<basic_expr<RTag, RArgs, RArity> > > > const\
    operator op(basic_expr<LTag, LArgs, LArity> const &left, basic_expr<RTag, RArgs, RArity> const &right)\
    {\
        basic_expr<tag, mpl::vector2<ref<basic_expr<LTag, LArgs, LArity> >, ref<basic_expr<RTag, RArgs, RArity> > > > that = {{left}, {right}};\
        return that;\
    }\
    /**/

    BOOST_PROTO_UNARY_OP(+, unary_plus_tag)
    BOOST_PROTO_UNARY_OP(-, unary_minus_tag)
    BOOST_PROTO_UNARY_OP(*, unary_star_tag)
    BOOST_PROTO_UNARY_OP(~, complement_tag)
    BOOST_PROTO_UNARY_OP(&, address_of_tag)
    BOOST_PROTO_UNARY_OP(!, logical_not_tag)
    BOOST_PROTO_UNARY_OP(++, pre_inc_tag)
    BOOST_PROTO_UNARY_OP(--, pre_dec_tag)

    BOOST_PROTO_BINARY_OP(<<, left_shift_tag)
    BOOST_PROTO_BINARY_OP(>>, right_shift_tag)
    BOOST_PROTO_BINARY_OP(*, multiply_tag)
    BOOST_PROTO_BINARY_OP(/, divide_tag)
    BOOST_PROTO_BINARY_OP(%, modulus_tag)
    BOOST_PROTO_BINARY_OP(+, add_tag)
    BOOST_PROTO_BINARY_OP(-, subtract_tag)
    BOOST_PROTO_BINARY_OP(<, less_tag)
    BOOST_PROTO_BINARY_OP(>, greater_tag)
    BOOST_PROTO_BINARY_OP(<=, less_equal_tag)
    BOOST_PROTO_BINARY_OP(>=, greater_equal_tag)
    BOOST_PROTO_BINARY_OP(==, equal_tag)
    BOOST_PROTO_BINARY_OP(!=, not_equal_tag)
    BOOST_PROTO_BINARY_OP(||, logical_or_tag)
    BOOST_PROTO_BINARY_OP(&&, logical_and_tag)
    BOOST_PROTO_BINARY_OP(&, bitand_tag)
    BOOST_PROTO_BINARY_OP(|, bitor_tag)
    BOOST_PROTO_BINARY_OP(^, bitxor_tag)
    BOOST_PROTO_BINARY_OP(BOOST_PP_COMMA(), comma_tag)
    BOOST_PROTO_BINARY_OP(->*, mem_ptr_tag)

    BOOST_PROTO_BINARY_OP(<<=, left_shift_assign_tag)
    BOOST_PROTO_BINARY_OP(>>=, right_shift_assign_tag)
    BOOST_PROTO_BINARY_OP(*=, multiply_assign_tag)
    BOOST_PROTO_BINARY_OP(/=, divide_assign_tag)
    BOOST_PROTO_BINARY_OP(%=, modulus_assign_tag)
    BOOST_PROTO_BINARY_OP(+=, add_assign_tag)
    BOOST_PROTO_BINARY_OP(-=, subtract_assign_tag)
    BOOST_PROTO_BINARY_OP(&=, bitand_assign_tag)
    BOOST_PROTO_BINARY_OP(|=, bitor_assign_tag)
    BOOST_PROTO_BINARY_OP(^=, bitxor_assign_tag)

    template<typename Tag, typename Args, long Arity>
    inline basic_expr<post_inc_tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > const
    operator ++(basic_expr<Tag, Args, Arity> const &arg, int)
    {
        basic_expr<post_inc_tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

    template<typename Tag, typename Args, long Arity>
    inline basic_expr<post_dec_tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > const
    operator --(basic_expr<Tag, Args, Arity> const &arg, int)
    {
        basic_expr<post_dec_tag, mpl::vector1<ref<basic_expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

#undef BOOST_PROTO_UNARY_OP
#undef BOOST_PROTO_BINARY_OP

}}

#endif
