///////////////////////////////////////////////////////////////////////////////
// regex_operators.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_XPRESSIVE_DETAIL_STATIC_REGEX_OPERATORS_HPP_EAN_10_04_2005
#define BOOST_XPRESSIVE_DETAIL_STATIC_REGEX_OPERATORS_HPP_EAN_10_04_2005

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/utility/enable_if.hpp>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/basic_regex.hpp>

namespace boost { namespace xpressive
{

///////////////////////////////////////////////////////////////////////////////
// operator +
template<typename BidiIterT>
inline proto::unary_op
<
    proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::unary_plus_tag
>
operator +(basic_regex<BidiIterT> const &regex)
{
    return +proto::noop(regex);
}

///////////////////////////////////////////////////////////////////////////////
// operator *
template<typename BidiIterT>
inline proto::unary_op
<
    proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::unary_star_tag
>
operator *(basic_regex<BidiIterT> const &regex)
{
    return *proto::noop(regex);
}

///////////////////////////////////////////////////////////////////////////////
// operator !
template<typename BidiIterT>
inline proto::unary_op
<
    proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::logical_not_tag
>
operator !(basic_regex<BidiIterT> const &regex)
{
    return !proto::noop(regex);
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename RightT, typename BidiIterT>
inline typename disable_if
<
    proto::is_op<RightT>
  , proto::binary_op
    <
        proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
      , proto::unary_op<RightT, proto::noop_tag>
      , proto::right_shift_tag
    >
>::type
operator >>(basic_regex<BidiIterT> const &regex, RightT const &right)
{
    return proto::noop(regex) >> proto::noop(right);
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename BidiIterT, typename LeftT>
inline typename disable_if
<
    proto::is_op<LeftT>
  , proto::binary_op
    <
        proto::unary_op<LeftT, proto::noop_tag>
      , proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
      , proto::right_shift_tag
    >
>::type
operator >>(LeftT const &left, basic_regex<BidiIterT> const &regex)
{
    return proto::noop(left) >> proto::noop(regex);
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename BidiIterT>
inline proto::binary_op
<
    proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::right_shift_tag
>
operator >>(basic_regex<BidiIterT> const &left, basic_regex<BidiIterT> const &right)
{
    return proto::noop(left) >> proto::noop(right);
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename RightT, typename BidiIterT>
inline typename disable_if
<
    proto::is_op<RightT>
  , proto::binary_op
    <
        proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
      , proto::unary_op<RightT, proto::noop_tag>
      , proto::bitor_tag
    >
>::type
operator |(basic_regex<BidiIterT> const &regex, RightT const &right)
{
    return proto::noop(regex) | proto::noop(right);
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename BidiIterT, typename LeftT>
inline typename disable_if
<
    proto::is_op<LeftT>
  , proto::binary_op
    <
        proto::unary_op<LeftT, proto::noop_tag>
      , proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
      , proto::bitor_tag
    >
>::type
operator |(LeftT const &left, basic_regex<BidiIterT> const &regex)
{
    return proto::noop(left) | proto::noop(regex);
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename BidiIterT>
inline proto::binary_op
<
    proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::unary_op<basic_regex<BidiIterT>, proto::noop_tag>
  , proto::bitor_tag
>
operator |(basic_regex<BidiIterT> const &left, basic_regex<BidiIterT> const &right)
{
    return proto::noop(left) | proto::noop(right);
}

}}

#endif
