
#ifndef BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED
#define BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED

// Copyright Eric Friedman 2002-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/aux_/partition_op.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/reverse_iter_fold.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template <
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct stable_partition
{
    typedef typename clear<Sequence>::type cleared_;
    typedef typename reverse_iter_fold<
          Sequence
        , pair< cleared_,cleared_ >
        , aux::partition_op<Predicate>
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,stable_partition,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, stable_partition)

}}

#endif // BOOST_MPL_STABLE_PARTITION_HPP_INCLUDED
