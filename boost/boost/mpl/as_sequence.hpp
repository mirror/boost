//-----------------------------------------------------------------------------
// boost mpl/as_sequence.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

#include "boost/mpl/is_sequence.hpp"
#include "boost/mpl/single_view.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

#if defined(BOOST_MPL_MSVC_60_ETI_BUG)
template<> struct as_sequence<int>
{
    typedef single_view<int> type;
};
#endif

BOOST_MPL_AUX_VOID_SPEC(1, as_sequence)

}} // namespace boost::mpl

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
