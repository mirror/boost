
#ifndef BOOST_MPL_SORT_HPP_INCLUDED
#define BOOST_MPL_SORT_HPP_INCLUDED

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

#include <boost/mpl/sort_fwd.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/sort_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template <
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct sort
    : sort_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Predicate >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,sort,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(1, sort)

}}

#endif // BOOST_MPL_SORT_HPP_INCLUDED
