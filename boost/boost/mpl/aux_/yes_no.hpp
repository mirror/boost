
#ifndef BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
#define BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/adl_barrier.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

namespace aux {

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};

template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};


template< BOOST_MPL_AUX_NTTP_DECL(long, n) > struct weighted_tag
{
#if !BOOST_WORKAROUND(BOOST_MSVC, == 1200)
    typedef char (&type)[n];
#else
    char buf[n];
    typedef weighted_tag type;
#endif
};

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x561)) \
    || BOOST_WORKAROUND(BOOST_MSVC, == 1300)
template<> struct weighted_tag<0>
{
    typedef char (&type)[1];
};
#endif

} // namespace aux

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
