//-----------------------------------------------------------------------------
// boost mpl/partition.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_PARTITION_HPP_INCLUDED
#define BOOST_MPL_PARTITION_HPP_INCLUDED

#include "boost/mpl/aux_/partition_op.hpp"
#include "boost/mpl/clear.hpp"
#include "boost/mpl/iter_fold.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/pair.hpp"
#include "boost/mpl/protect.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template <
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Predicate)
    >
struct partition
{
private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename clear<Sequence>::type cleared_;

public:
    typedef typename iter_fold<
          Sequence
        , pair< cleared_,cleared_ >
        , protect< aux::partition_op<pred_> >
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,partition,(Sequence,Predicate))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

BOOST_MPL_AUX_ALGORITHM_VOID_SPEC(2, partition)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_PARTITION_HPP_INCLUDED
