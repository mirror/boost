///////////////////////////////////////////////////////////////////////////////
/// \file proto_typeof.hpp
/// Type registrations so that proto expression templates can be used together
/// with the Boost.Typeof library.
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_PROTO_PROTO_TYPEOF_H
#define BOOST_XPRESSIVE_PROTO_PROTO_TYPEOF_H

#include <boost/xpressive/proto/detail/prefix.hpp>
#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/deep_copy.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#include <boost/xpressive/proto/detail/suffix.hpp>

BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::terminal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::posit)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::negate)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::dereference)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::complement)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::address_of)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_not)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::left_shift)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::right_shift)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multiplies)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divides)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::plus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::minus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::equal_to)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::not_equal_to)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_and)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_and)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_xor)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::comma)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::mem_ptr)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::left_shift_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::right_shift_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multilpies_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divides_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::plus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::minus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_and_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_or_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_xor_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::subscript)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::function)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::ref, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::expr, (typename)(typename)(long))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::literal, (typename)(typename))

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args1, 1)
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args2, 2)
// can't use PP metaprogramming here because all typeof registrations
// must be on separate lines.
#if BOOST_PROTO_MAX_ARITY >= 3
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args3, 3)
#endif
#if BOOST_PROTO_MAX_ARITY >= 4
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args4, 4)
#endif
#if BOOST_PROTO_MAX_ARITY >= 5
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args5, 5)
#endif
#if BOOST_PROTO_MAX_ARITY >= 6
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args6, 6)
#endif
#if BOOST_PROTO_MAX_ARITY >= 7
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args7, 7)
#endif
#if BOOST_PROTO_MAX_ARITY >= 8
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args8, 8)
#endif
#if BOOST_PROTO_MAX_ARITY >= 9
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args9, 9)
#endif
#if BOOST_PROTO_MAX_ARITY >= 10
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args10, 10)
#endif
#if BOOST_PROTO_MAX_ARITY >= 11
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args11, 11)
#endif
#if BOOST_PROTO_MAX_ARITY >= 12
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args12, 12)
#endif
#if BOOST_PROTO_MAX_ARITY >= 13
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args13, 13)
#endif
#if BOOST_PROTO_MAX_ARITY >= 14
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args14, 14)
#endif
#if BOOST_PROTO_MAX_ARITY >= 15
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args15, 15)
#endif
#if BOOST_PROTO_MAX_ARITY >= 16
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args16, 16)
#endif
#if BOOST_PROTO_MAX_ARITY >= 17
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args17, 17)
#endif
#if BOOST_PROTO_MAX_ARITY >= 18
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args18, 18)
#endif
#if BOOST_PROTO_MAX_ARITY >= 19
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args19, 19)
#endif
#if BOOST_PROTO_MAX_ARITY >= 20
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::args20, 20)
#endif

#define BOOST_PROTO_AUTO(Var, Expr) BOOST_AUTO(Var, boost::proto::deep_copy(Expr))
#define BOOST_PROTO_AUTO_TPL(Var, Expr) BOOST_AUTO_TPL(Var, boost::proto::deep_copy(Expr))

#endif
