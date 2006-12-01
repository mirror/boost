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

    BOOST_PROTO_UNARY_OP(+, tag::unary_plus)
    BOOST_PROTO_UNARY_OP(-, tag::unary_minus)
    BOOST_PROTO_UNARY_OP(*, tag::unary_star)
    BOOST_PROTO_UNARY_OP(~, tag::complement)
    BOOST_PROTO_UNARY_OP(&, tag::address_of)
    BOOST_PROTO_UNARY_OP(!, tag::logical_not)
    BOOST_PROTO_UNARY_OP(++, tag::pre_inc)
    BOOST_PROTO_UNARY_OP(--, tag::pre_dec)

    BOOST_PROTO_BINARY_OP(<<, tag::left_shift)
    BOOST_PROTO_BINARY_OP(>>, tag::right_shift)
    BOOST_PROTO_BINARY_OP(*, tag::multiply)
    BOOST_PROTO_BINARY_OP(/, tag::divide)
    BOOST_PROTO_BINARY_OP(%, tag::modulus)
    BOOST_PROTO_BINARY_OP(+, tag::add)
    BOOST_PROTO_BINARY_OP(-, tag::subtract)
    BOOST_PROTO_BINARY_OP(<, tag::less)
    BOOST_PROTO_BINARY_OP(>, tag::greater)
    BOOST_PROTO_BINARY_OP(<=, tag::less_equal)
    BOOST_PROTO_BINARY_OP(>=, tag::greater_equal)
    BOOST_PROTO_BINARY_OP(==, tag::equal)
    BOOST_PROTO_BINARY_OP(!=, tag::not_equal)
    BOOST_PROTO_BINARY_OP(||, tag::logical_or)
    BOOST_PROTO_BINARY_OP(&&, tag::logical_and)
    BOOST_PROTO_BINARY_OP(&, tag::bitwise_and)
    BOOST_PROTO_BINARY_OP(|, tag::bitwise_or)
    BOOST_PROTO_BINARY_OP(^, tag::bitwise_xor)
    BOOST_PROTO_BINARY_OP(BOOST_PP_COMMA(), tag::comma)
    BOOST_PROTO_BINARY_OP(->*, tag::mem_ptr)

    BOOST_PROTO_BINARY_OP(<<=, tag::left_shift_assign)
    BOOST_PROTO_BINARY_OP(>>=, tag::right_shift_assign)
    BOOST_PROTO_BINARY_OP(*=, tag::multiply_assign)
    BOOST_PROTO_BINARY_OP(/=, tag::divide_assign)
    BOOST_PROTO_BINARY_OP(%=, tag::modulus_assign)
    BOOST_PROTO_BINARY_OP(+=, tag::add_assign)
    BOOST_PROTO_BINARY_OP(-=, tag::subtract_assign)
    BOOST_PROTO_BINARY_OP(&=, tag::bitwise_and_assign)
    BOOST_PROTO_BINARY_OP(|=, tag::bitwise_or_assign)
    BOOST_PROTO_BINARY_OP(^=, tag::bitwise_xor_assign)

    template<typename Tag, typename Args, long Arity>
    inline expr<tag::post_inc, args1<ref<expr<Tag, Args, Arity> > > > const
    operator ++(expr<Tag, Args, Arity> const &arg, int)
    {
        expr<tag::post_inc, args1<ref<expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

    template<typename Tag, typename Args, long Arity>
    inline expr<tag::post_dec, args1<ref<expr<Tag, Args, Arity> > > > const
    operator --(expr<Tag, Args, Arity> const &arg, int)
    {
        expr<tag::post_dec, args1<ref<expr<Tag, Args, Arity> > > > that = {{arg}};
        return that;
    }

#undef BOOST_PROTO_UNARY_OP
#undef BOOST_PROTO_BINARY_OP

}}

#endif
