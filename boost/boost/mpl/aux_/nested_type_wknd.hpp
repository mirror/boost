//-----------------------------------------------------------------------------
// boost mpl/aux_/nested_type_wknd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(__GNUC__) && (__GNUC__ < 3 || __GNUC__ == 3 && __GNUC_MINOR__ <= 2 \
    || !defined(BOOST_STRICT_CONFIG)) \
 || defined(__BORLANDC__) && (__BORLANDC__ <= 0x561 || !defined(BOOST_STRICT_CONFIG)) \
 || defined(__SUNPRO_CC)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct nested_type_wknd
    : T::type
{
};

}}} // namespace boost::mpl::aux

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) ::boost::mpl::aux::nested_type_wknd<T>

#else

#   define BOOST_MPL_AUX_NESTED_TYPE_WKND(T) T::type

#endif // __GNUC__

#endif // BOOST_MPL_AUX_NESTED_TYPE_WKND_HPP_INCLUDED
