///////////////////////////////////////////////////////////////////////////////
// operators.hpp
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
#include <boost/xpressive/proto/op_tags.hpp>
#include <boost/xpressive/proto/op_base.hpp>

namespace boost { namespace proto
{
    ///////////////////////////////////////////////////////////////////////////////
    // unary_op_generator
    template<typename ArgT, typename TagT>
    struct unary_op_generator
    {
        typedef unary_op<
            typename as_op<ArgT>::type
          , TagT
        > type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // binary_op_generator
    template<typename LeftT, typename RightT, typename TagT>
    struct binary_op_generator
    {
        typedef binary_op<
            typename as_op<LeftT>::type
          , typename as_op<RightT>::type
          , TagT
        > type;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // unary operators
    template<typename ArgT>
    unary_op<ArgT, noop_tag> const
    noop(ArgT const &arg)
    {
        return make_op<noop_tag>(arg);
    }

#define BOOST_PROTO_UNARY_OP(op, tag)                                                           \
    template<typename ArgT>                                                                     \
    inline typename lazy_enable_if<is_op<ArgT>, unary_op_generator<ArgT, tag> >::type const     \
    operator op(ArgT const &arg)                                                                \
    {                                                                                           \
        return make_op<tag>(as_op<ArgT>::make(arg));                                            \
    }

#define BOOST_PROTO_BINARY_OP(op, tag)                                                          \
    template<typename LeftT, typename RightT>                                                   \
    inline typename lazy_enable_if<                                                             \
        mpl::or_<is_op<LeftT>, is_op<RightT> >                                                  \
      , binary_op_generator<LeftT, RightT, tag>                                                 \
    >::type const                                                                               \
    operator op(LeftT const &left, RightT const &right)                                         \
    {                                                                                           \
        return make_op<tag>(as_op<LeftT>::make(left), as_op<RightT>::make(right));              \
    }

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

#undef BOOST_PROTO_BINARY_OP
#undef BOOST_PROTO_UNARY_OP

    ///////////////////////////////////////////////////////////////////////////////
    // post-fix operators
    template<typename ArgT>
    inline typename lazy_enable_if<is_op<ArgT>, unary_op_generator<ArgT, post_inc_tag> >::type const
    operator ++(ArgT const &arg, int)
    {
        return make_op<post_inc_tag>(arg.cast());
    }

    template<typename ArgT>
    inline typename lazy_enable_if<is_op<ArgT>, unary_op_generator<ArgT, post_dec_tag> >::type const
    operator --(ArgT const &arg, int)
    {
        return make_op<post_dec_tag>(arg.cast());
    }

}}

#endif
