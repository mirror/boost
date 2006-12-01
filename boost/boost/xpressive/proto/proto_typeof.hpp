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

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/config.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/xpressive/proto/proto_fwd.hpp>
#include <boost/xpressive/proto/deep_copy.hpp>

#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()

BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::unary)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::binary)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::nary)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::terminal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::unary_plus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::unary_minus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::unary_star)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::complement)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::address_of)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_not)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::pre_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_inc)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::post_dec)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::left_shift)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::right_shift)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multiply)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divide)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::add)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::subtract)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::less_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::greater_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::not_equal)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::logical_and)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitand)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitwise_or)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitxor)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::comma)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::mem_ptr)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::left_shift_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::right_shift_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::multiply_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::divide_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::modulus_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::add_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::subtract_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitand_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitor_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::bitxor_assign)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::subscript)
BOOST_TYPEOF_REGISTER_TYPE(boost::proto::tag::function)

BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::ref, (typename))
BOOST_TYPEOF_REGISTER_TEMPLATE(boost::proto::expr, (typename)(typename)(long))

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

#define BOOST_PROTO_AUTO(Var, Expr) BOOST_AUTO(Var, boost::proto::deep_copy(Expr))
#define BOOST_PROTO_AUTO_TPL(Var, Expr) BOOST_AUTO_TPL(Var, boost::proto::deep_copy(Expr))

#endif
