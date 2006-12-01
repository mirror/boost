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
#include <boost/xpressive/proto/expr.hpp>

namespace boost { namespace proto
{
#define BOOST_PROTO_UNARY_OP(op, tag)\
    template<typename Tag, typename Args, long Arity>\
    inline expr<tag, args1<ref<expr<Tag, Args, Arity> > > > const\
    operator op(expr<Tag, Args, Arity> const &arg)\
    {\
        expr<tag, args1<ref<expr<Tag, Args, Arity> > > > that = {{arg}};\
        return that;\
    }\
    /**/

#define BOOST_PROTO_BINARY_OP(op, tag)\
    template<typename LTag, typename LArgs, long LArity, typename Right>\
    inline expr<tag, args2<ref<expr<LTag, LArgs, LArity> >, typename meta::as_expr_ref<Right>::type> > const\
    operator op(expr<LTag, LArgs, LArity> const &left, Right const &right)\
    {\
        expr<tag, args2<ref<expr<LTag, LArgs, LArity> >, typename meta::as_expr_ref<Right>::type> > that = {{left}, proto::as_expr_ref(right)};\
        return that;\
    }\
    template<typename Left, typename RTag, typename RArgs, long RArity>\
    inline expr<tag, args2<typename meta::as_expr_ref<Left>::type, ref<expr<RTag, RArgs, RArity> > > > const\
    operator op(Left const &left, expr<RTag, RArgs, RArity> const &right)\
    {\
        expr<tag, args2<typename meta::as_expr_ref<Left>::type, ref<expr<RTag, RArgs, RArity> > > > that = {proto::as_expr_ref(left), {right}};\
        return that;\
    }\
    template<typename LTag, typename LArgs, long LArity, typename RTag, typename RArgs, long RArity>\
    inline expr<tag, args2<ref<expr<LTag, LArgs, LArity> >, ref<expr<RTag, RArgs, RArity> > > > const\
    operator op(expr<LTag, LArgs, LArity> const &left, expr<RTag, RArgs, RArity> const &right)\
    {\
        expr<tag, args2<ref<expr<LTag, LArgs, LArity> >, ref<expr<RTag, RArgs, RArity> > > > that = {{left}, {right}};\
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
    BOOST_PROTO_BINARY_OP(&, bitwise_and_tag)
    BOOST_PROTO_BINARY_OP(|, bitwise_or_tag)
    BOOST_PROTO_BINARY_OP(^, bitwise_xor_tag)
    BOOST_PROTO_BINARY_OP(BOOST_PP_COMMA(), comma_tag)
    BOOST_PROTO_BINARY_OP(->*, mem_ptr_tag)

    BOOST_PROTO_BINARY_OP(<<=, left_shift_assign_tag)
    BOOST_PROTO_BINARY_OP(>>=, right_shift_assign_tag)
    BOOST_PROTO_BINARY_OP(*=, multiply_assign_tag)
    BOOST_PROTO_BINARY_OP(/=, divide_assign_tag)
    BOOST_PROTO_BINARY_OP(%=, modulus_assign_tag)
    BOOST_PROTO_BINARY_OP(+=, add_assign_tag)
    BOOST_PROTO_BINARY_OP(-=, subtract_assign_tag)
    BOOST_PROTO_BINARY_OP(&=, bitwise_and_assign_tag)
    BOOST_PROTO_BINARY_OP(|=, bitwise_or_assign_tag)
    BOOST_PROTO_BINARY_OP(^=, bitwise_xor_assign_tag)

    template<typename Tag, typename Args, long Arity>
    inline expr<post_inc_tag, args1<ref<expr<Tag, Args, Arity> > > > const
    operator ++(expr<Tag, Args, Arity> const &arg, int)
    {
        expr<post_inc_tag, args1<ref<expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

    template<typename Tag, typename Args, long Arity>
    inline expr<post_dec_tag, args1<ref<expr<Tag, Args, Arity> > > > const
    operator --(expr<Tag, Args, Arity> const &arg, int)
    {
        expr<post_dec_tag, args1<ref<expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

#undef BOOST_PROTO_UNARY_OP
#undef BOOST_PROTO_BINARY_OP

}}

#endif
