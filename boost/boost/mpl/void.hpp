
#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

// + file: boost/mpl/void.hpp
// + last modified: 05/may/03

// Copyright (c) 2001-03
// Peter Dimov, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/void_fwd.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/config/msvc.hpp"
#include "boost/mpl/aux_/config/workaround.hpp"

namespace boost {
namespace mpl {

//  [JDG Feb-4-2003] made void_ a complete type to allow it to be
//  instantiated so that it can be passed in as an object that can be
//  used to select an overloaded function. Possible use includes signaling
//  a zero arity functor evaluation call.
struct void_ { typedef void_ type; };

template< typename T >
struct is_void_
    : false_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using false_::value;
#endif
};

template<>
struct is_void_<void_>
    : true_
{
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    using true_::value;
#endif
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VOID_HPP_INCLUDED
