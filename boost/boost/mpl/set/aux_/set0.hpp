
#ifndef BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/long.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Dummy = na > struct set0
{
    typedef aux::set_tag    tag;
    typedef void_           last_masked_;
    typedef void_           item_type_;
    typedef item_type_      type;
    typedef long_<0>        size;
    typedef long_<1>        order;
};

}}

#endif // BOOST_MPL_SET_AUX_SET0_HPP_INCLUDED
