
#ifndef BOOST_MPL_REPLACE_HPP_INCLUDED
#define BOOST_MPL_REPLACE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright John R. Bandela 2000-2002
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

#include <boost/mpl/replace_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(replace)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(OldType)
    , typename BOOST_MPL_AUX_NA_PARAM(NewType)
    >
struct replace
    : replace_if< Sequence, same_as<OldType>, NewType >
{
};

BOOST_MPL_AUX_NA_SPEC(3, replace)

}}

#endif // BOOST_MPL_REPLACE_HPP_INCLUDED
