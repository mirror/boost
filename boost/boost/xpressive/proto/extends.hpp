///////////////////////////////////////////////////////////////////////////////
/// \file entends.hpp
/// A base class for defining end-user expression types
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006
#define BOOST_PROTO_EXTENDS_HPP_EAN_11_1_2006

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/xpressive/proto/ref.hpp>
#include <boost/xpressive/proto/traits.hpp>
#include <boost/xpressive/proto/basic_expr.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#ifndef BOOST_PROTO_EXTENDS_TAG_MAX_ARITY
# define BOOST_PROTO_EXTENDS_TAG_MAX_ARITY BOOST_PROTO_MAX_ARITY
#endif

namespace boost { namespace proto
{

    namespace extends_private_
    {
        struct extends_base
        {};

    #define BOOST_PROTO_EXTENDS_BINARY_OP(op, tag)\
        template<typename Left, typename Right>\
        typename enable_if<\
            mpl::and_<meta::is_extends<Left>, meta::is_extends<Right> >\
          , basic_expr<tag, mpl::vector2<ref<typename Left::expr_type>, ref<typename Left::expr_type> > > const\
        >::type\
        operator op(Left const &left, Right const &right)\
        {\
            return left.cast() op right.cast();\
        }\
        /**/

        BOOST_PROTO_EXTENDS_BINARY_OP(<<, left_shift_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(>>, right_shift_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(*, multiply_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(/, divide_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(%, modulus_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(+, add_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(-, subtract_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(<, less_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(>, greater_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(<=, less_equal_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(>=, greater_equal_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(==, equal_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(!=, not_equal_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(||, logical_or_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(&&, logical_and_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(&, bitand_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(|, bitor_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(^, bitxor_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(BOOST_PP_COMMA(), comma_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(->*, mem_ptr_tag)

        BOOST_PROTO_EXTENDS_BINARY_OP(<<=, left_shift_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(>>=, right_shift_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(*=, multiply_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(/=, divide_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(%=, modulus_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(+=, add_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(-=, subtract_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(&=, bitand_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(|=, bitor_assign_tag)
        BOOST_PROTO_EXTENDS_BINARY_OP(^=, bitxor_assign_tag)
    
    #undef BOOST_PROTO_EXTENDS_BINARY_OP
    }

    template<typename Expr>
    struct extends
      : Expr
      , extends_private_::extends_base
    {
        BOOST_MPL_ASSERT((meta::is_basic_expr<Expr>));
        typedef Expr type;

        extends()
          : Expr()
        {}

        void assign(Expr const &that)
        {
            *static_cast<Expr *>(this) = that;
        }

        using Expr::operator =;
    };

}}

#endif
