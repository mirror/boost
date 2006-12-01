///////////////////////////////////////////////////////////////////////////////
/// \file tags.hpp
/// Contains the tags for all the overloadable operators in C++, as well as
/// the base tags unary, binary and nary, as well as the is_unary\<\>,
/// is_binary\<\> and is_nary\<\> predicates.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_OP_TAGS_HPP_EAN_04_01_2005
#define BOOST_PROTO_OP_TAGS_HPP_EAN_04_01_2005

#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace tag
{

    ///////////////////////////////////////////////////////////////////////////////
    // Operator tags
    struct unary {};
    struct binary {};
    struct nary {}; // for operator()

    struct terminal : unary {};
    struct unary_plus : unary {};
    struct unary_minus : unary {};
    struct unary_star : unary {};
    struct complement : unary {};
    struct address_of : unary {};
    struct logical_not : unary {};
    struct pre_inc : unary {};
    struct pre_dec : unary {};
    struct post_inc : unary {};
    struct post_dec : unary {};
    
    struct left_shift : binary {};
    struct right_shift : binary {};
    struct multiply : binary {};
    struct divide : binary {};
    struct modulus : binary {};
    struct add : binary {};
    struct subtract : binary {};
    struct less : binary {};
    struct greater : binary {};
    struct less_equal : binary {};
    struct greater_equal : binary {};
    struct equal : binary {};
    struct not_equal : binary {};
    struct logical_or : binary {};
    struct logical_and : binary {};
    struct bitwise_and : binary {};
    struct bitwise_or : binary {};
    struct bitwise_xor : binary {};
    struct comma : binary {};
    struct mem_ptr : binary {};

    struct assign : binary {};
    struct left_shift_assign : binary {};
    struct right_shift_assign : binary {};
    struct multiply_assign : binary {};
    struct divide_assign : binary {};
    struct modulus_assign : binary {};
    struct add_assign : binary {};
    struct subtract_assign : binary {};
    struct bitwise_and_assign : binary {};
    struct bitwise_or_assign : binary {};
    struct bitwise_xor_assign : binary {};
    struct subscript : binary {};

    struct function : nary {};

}}}

#endif
