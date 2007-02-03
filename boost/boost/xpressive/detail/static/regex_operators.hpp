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

// BUGBUG store by reference here!!!

///////////////////////////////////////////////////////////////////////////////
// operator +
template<typename BidiIter>
inline typename proto::unary_plus<
    typename proto::terminal<basic_regex<BidiIter> >::type
>::type
operator +(basic_regex<BidiIter> const &regex)
{
    typename proto::unary_plus<
        typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{regex}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator *
template<typename BidiIter>
inline typename proto::unary_star<
    typename proto::terminal<basic_regex<BidiIter> >::type
>::type
operator *(basic_regex<BidiIter> const &regex)
{
    typename proto::unary_star<
        typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{regex}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator !
template<typename BidiIter>
inline typename proto::logical_not<
    typename proto::terminal<basic_regex<BidiIter> >::type
>::type
operator !(basic_regex<BidiIter> const &regex)
{
    typename proto::logical_not<
        typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{regex}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename Right, typename BidiIter>
inline typename lazy_disable_if
<
    proto::is_expr<Right>
  , proto::right_shift<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<Right>::type
    >
>::type
operator >>(basic_regex<BidiIter> const &regex, Right const &right)
{
    typename proto::right_shift<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<Right>::type
    >::type that = {{regex}, {right}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename BidiIter, typename Left>
inline typename lazy_disable_if
<
    proto::is_expr<Left>
  , proto::right_shift<
        typename proto::terminal<Left>::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >
>::type
operator >>(Left const &left, basic_regex<BidiIter> const &regex)
{
    typename proto::right_shift<
        typename proto::terminal<Left>::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{left}, {regex}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator >>
template<typename BidiIter>
inline typename proto::right_shift<
    typename proto::terminal<basic_regex<BidiIter> >::type
  , typename proto::terminal<basic_regex<BidiIter> >::type
>::type
operator >>(basic_regex<BidiIter> const &left, basic_regex<BidiIter> const &right)
{
    typename proto::right_shift<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{left}, {right}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename Right, typename BidiIter>
inline typename lazy_disable_if
<
    proto::is_expr<Right>
  , proto::bitwise_or<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<Right>::type
    >
>::type
operator |(basic_regex<BidiIter> const &regex, Right const &right)
{
    typename proto::bitwise_or<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<Right>::type
    >::type that = {{regex}, {right}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename BidiIter, typename Left>
inline typename lazy_disable_if
<
    proto::is_expr<Left>
  , proto::bitwise_or<
        typename proto::terminal<Left>::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >
>::type
operator |(Left const &left, basic_regex<BidiIter> const &regex)
{
    typename proto::bitwise_or<
        typename proto::terminal<Left>::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{left}, {regex}};
    return that;
}

///////////////////////////////////////////////////////////////////////////////
// operator |
template<typename BidiIter>
inline typename proto::bitwise_or<
    typename proto::terminal<basic_regex<BidiIter> >::type
  , typename proto::terminal<basic_regex<BidiIter> >::type
>::type
operator |(basic_regex<BidiIter> const &left, basic_regex<BidiIter> const &right)
{
    typename proto::bitwise_or<
        typename proto::terminal<basic_regex<BidiIter> >::type
      , typename proto::terminal<basic_regex<BidiIter> >::type
    >::type that = {{left}, {right}};
    return that;
}

}}

#endif
