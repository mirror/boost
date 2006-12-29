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
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/tags.hpp>
#include <boost/xpressive/proto/expr.hpp>

namespace boost { namespace proto
{
    namespace detail
    {
        template<typename Tag, typename Left, typename Right, typename Enable1 = void, typename Enable2 = void>
        struct as_expr_if2
        {};

        template<typename Tag, typename Left, typename Right>
        struct as_expr_if2<Tag, Left, Right, typename Left::is_boost_proto_expr_, void>
        {
            typedef expr<
                Tag
              , args2<
                    ref<typename Left::boost_proto_expr_type_>
                  , expr<tag::terminal, args1<Right const &> >
                >
            > type;

            static type make(Left const &left, Right const &right)
            {
                type that = {{left.cast()}, {right}};
                return that;
            }
        };

        template<typename Tag, typename Left, typename Right>
        struct as_expr_if2<Tag, Left, Right, void, typename Right::is_boost_proto_expr_>
        {
            typedef expr<
                Tag
              , args2<
                    expr<tag::terminal, args1<Left const &> >
                  , ref<typename Right::boost_proto_expr_type_>
                >
            > type;

            static type make(Left const &left, Right const &right)
            {
                type that = {{left}, {right.cast()}};
                return that;
            }
        };

        template<typename Tag, typename Left, typename Right, typename Enable1 = void, typename Enable2 = void>
        struct as_expr_if
          : as_expr_if2<Tag, Left, Right>
        {};

        template<typename Tag, typename Left, typename Right>
        struct as_expr_if<Tag, Left, Right, typename Left::is_boost_proto_expr_, typename Right::is_boost_proto_expr_>
        {
            typedef expr<
                Tag
              , args2<
                    ref<typename Left::boost_proto_expr_type_>
                  , ref<typename Right::boost_proto_expr_type_>
                >
            > type;

            static type make(Left const &left, Right const &right)
            {
                type that = {{left.cast()}, {right.cast()}};
                return that;
            }
        };
    }

#define BOOST_PROTO_UNARY_OP(op, tag)\
    template<typename Arg>\
    inline expr<tag, args1<ref<typename Arg::boost_proto_expr_type_> > > const\
    operator op(Arg const &arg)\
    {\
        expr<tag, args1<ref<typename Arg::boost_proto_expr_type_> > > that = {{arg.cast()}};\
        return that;\
    }\
    /**/

#define BOOST_PROTO_BINARY_OP(op, tag)\
    template<typename Left, typename Right>\
    inline typename detail::as_expr_if<tag, Left, Right>::type const\
    operator op(Left const &left, Right const &right)\
    {\
        return detail::as_expr_if<tag, Left, Right>::make(left, right);\
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

    template<typename Arg>
    inline expr<tag::post_inc, args1<ref<typename Arg::boost_proto_expr_type_> > > const
    operator ++(Arg const &arg, int)
    {
        expr<tag::post_inc, args1<ref<typename Arg::boost_proto_expr_type_> > > that = {{arg.cast()}};
        return that;
    }

    template<typename Arg>
    inline expr<tag::post_dec, args1<ref<typename Arg::boost_proto_expr_type_> > > const
    operator --(Arg const &arg, int)
    {
        expr<tag::post_dec, args1<ref<typename Arg::boost_proto_expr_type_> > > that = {{arg.cast()}};
        return that;
    }

#undef BOOST_PROTO_UNARY_OP
#undef BOOST_PROTO_BINARY_OP

}}

#endif
