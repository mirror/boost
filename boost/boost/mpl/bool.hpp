
#ifndef BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_MPL_BOOL_HPP_INCLUDED

// + file: boost/mpl/bool.hpp
// + last modified: 12/apr/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/bool_fwd.hpp"
#include "boost/mpl/aux_/config/static_constant.hpp"

namespace boost { namespace mpl {

template< bool C_ > struct bool_
{
    BOOST_STATIC_CONSTANT(bool, value = C_);
    typedef bool_ type;
    typedef bool value_type;
    operator bool() const { return this->value; }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

}} // namespace boost::mpl

#endif // BOOST_MPL_BOOL_HPP_INCLUDED
