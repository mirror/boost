//-----------------------------------------------------------------------------
// boost mpl/vector/vector0_c.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_VECTOR_VECTOR0_C_HPP_INCLUDED
#define BOOST_MPL_VECTOR_VECTOR0_C_HPP_INCLUDED

#include "boost/mpl/vector/vector0.hpp"

namespace boost {
namespace mpl {

template< typename T > struct vector0_c
    : vector0<>
{
    typedef vector0_c type;
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_VECTOR0_C_HPP_INCLUDED
