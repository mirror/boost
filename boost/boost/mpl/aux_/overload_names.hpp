
#ifndef BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED
#define BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300) \
    || BOOST_WORKAROUND(__EDG_VERSION__, <= 245)

#   define BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY  operator/
#   define BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER operator|
#   define BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY  operator||
#   define BOOST_MPL_AUX_OVERLOAD_IS_MASKED     operator%

#   define BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY(x, y)   x / y
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER(x, y)  x | y
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY(x, y)   x || y
#   define BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED(x, y)      x % y

#else

#   define BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY  value_by_key_
#   define BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER item_by_order_
#   define BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY  order_by_key_
#   define BOOST_MPL_AUX_OVERLOAD_IS_MASKED     is_masked_

#   define BOOST_MPL_AUX_OVERLOAD_CALL_VALUE_BY_KEY     BOOST_MPL_AUX_OVERLOAD_VALUE_BY_KEY
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ITEM_BY_ORDER    BOOST_MPL_AUX_OVERLOAD_ITEM_BY_ORDER
#   define BOOST_MPL_AUX_OVERLOAD_CALL_ORDER_BY_KEY     BOOST_MPL_AUX_OVERLOAD_ORDER_BY_KEY
#   define BOOST_MPL_AUX_OVERLOAD_CALL_IS_MASKED        BOOST_MPL_AUX_OVERLOAD_IS_MASKED

#endif

#endif // BOOST_MPL_AUX_OVERLOAD_NAMES_HPP_INCLUDED
