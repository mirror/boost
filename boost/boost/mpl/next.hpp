//-----------------------------------------------------------------------------
// boost mpl/next.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_NEXT_HPP_INCLUDED
#define BOOST_MPL_NEXT_HPP_INCLUDED

#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

#if defined(BOOST_MPL_MSVC_ETI_BUG)
template<> struct next<int>
{
    typedef int type;
};
#endif

BOOST_MPL_AUX_VOID_SPEC(1, next)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_NEXT_HPP_INCLUDED
