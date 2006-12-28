///////////////////////////////////////////////////////////////////////////////
/// \file entends.hpp
/// A base class for defining end-user expression types
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/mpl/bool.hpp>
#include <boost/xpressive/proto/ref.hpp>
#include <boost/xpressive/proto/args.hpp>
#include <boost/xpressive/proto/expr.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>

namespace boost { namespace proto { namespace extends_private_
{
    template<typename Expr>
    struct extends
      : Expr
    {
        typedef Expr type;
        typedef Expr boost_proto_extends_private_extends_expr_type_;
        typedef void is_boost_proto_extends_private_extends_;

        extends()
          : Expr()
        {}

        extends(Expr const &expr)
          : Expr(expr)
        {}

        void assign(Expr const &that)
        {
            *static_cast<Expr *>(this) = that;
        }

        using Expr::operator =;
    };

#define BOOST_PROTO_EXTENDS_BINARY_OP(op, tag)\
    template<typename Left, typename Right>\
    expr<tag, args2<\
        ref<typename Left::boost_proto_extends_private_extends_expr_type_>\
      , ref<typename Right::boost_proto_extends_private_extends_expr_type_>\
    > > const\
    operator op(Left const &left, Right const &right)\
    {\
        return left.cast() op right.cast();\
    }\
    /**/

    BOOST_PROTO_EXTENDS_BINARY_OP(<<, tag::left_shift)
    BOOST_PROTO_EXTENDS_BINARY_OP(>>, tag::right_shift)
    BOOST_PROTO_EXTENDS_BINARY_OP(*, tag::multiply)
    BOOST_PROTO_EXTENDS_BINARY_OP(/, tag::divide)
    BOOST_PROTO_EXTENDS_BINARY_OP(%, tag::modulus)
    BOOST_PROTO_EXTENDS_BINARY_OP(+, tag::add)
    BOOST_PROTO_EXTENDS_BINARY_OP(-, tag::subtract)
    BOOST_PROTO_EXTENDS_BINARY_OP(<, tag::less)
    BOOST_PROTO_EXTENDS_BINARY_OP(>, tag::greater)
    BOOST_PROTO_EXTENDS_BINARY_OP(<=, tag::less_equal)
    BOOST_PROTO_EXTENDS_BINARY_OP(>=, tag::greater_equal)
    BOOST_PROTO_EXTENDS_BINARY_OP(==, tag::equal)
    BOOST_PROTO_EXTENDS_BINARY_OP(!=, tag::not_equal)
    BOOST_PROTO_EXTENDS_BINARY_OP(||, tag::logical_or)
    BOOST_PROTO_EXTENDS_BINARY_OP(&&, tag::logical_and)
    BOOST_PROTO_EXTENDS_BINARY_OP(&, tag::bitwise_and)
    BOOST_PROTO_EXTENDS_BINARY_OP(|, tag::bitwise_or)
    BOOST_PROTO_EXTENDS_BINARY_OP(^, tag::bitwise_xor)
    BOOST_PROTO_EXTENDS_BINARY_OP(BOOST_PP_COMMA(), tag::comma)
    BOOST_PROTO_EXTENDS_BINARY_OP(->*, tag::mem_ptr)

    BOOST_PROTO_EXTENDS_BINARY_OP(<<=, tag::left_shift_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(>>=, tag::right_shift_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(*=, tag::multiply_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(/=, tag::divide_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(%=, tag::modulus_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(+=, tag::add_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(-=, tag::subtract_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(&=, tag::bitwise_and_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(|=, tag::bitwise_or_assign)
    BOOST_PROTO_EXTENDS_BINARY_OP(^=, tag::bitwise_xor_assign)

#undef BOOST_PROTO_EXTENDS_BINARY_OP

}}}

#endif
