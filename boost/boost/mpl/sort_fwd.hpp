
#ifndef BOOST_MPL_SORT_FWD_HPP_INCLUDED
#define BOOST_MPL_SORT_FWD_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/common_name_wknd.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(sort)

template< typename Tag > struct sort_impl;
template< typename Sequence, typename Predicate > struct sort;

}}

#endif // BOOST_MPL_SORT_FWD_HPP_INCLUDED
