//-----------------------------------------------------------------------------
// boost mpl/project2nd.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_PROJECT2ND_HPP_INCLUDED
#define BOOST_MPL_PROJECT2ND_HPP_INCLUDED

#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T1)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T2)
    >
struct project2nd
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,project2nd,(T1,T2))
};

BOOST_MPL_AUX_VOID_SPEC(2, project2nd)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_PROJECT2ND_HPP_INCLUDED
