//-----------------------------------------------------------------------------
// boost mpl/aux_/msvc_never_true.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

#include "boost/config.hpp"

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300

namespace boost {
namespace mpl {
namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MSVC < 1300

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
