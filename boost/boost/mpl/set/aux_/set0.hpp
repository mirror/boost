
#ifndef BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

// + file: boost/mpl/aux_/set0.hpp
// + last modified: 03/may/03

// Copyright (c) 2002-03
// David Abrahams, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/void_fwd.hpp"
#include "boost/mpl/set/aux_/tag.hpp"
#include "boost/mpl/aux_/config/static_constant.hpp"

namespace boost {
namespace mpl {

template< int p_ = 0 > struct set0
{
    typedef aux::set_tag    tag;
    typedef void_           last_masked;
    typedef void_           item;

    BOOST_STATIC_CONSTANT(long, order = 0);
};

}}

#endif // BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
