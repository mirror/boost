//-----------------------------------------------------------------------------
// boost mpl/sort.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002-2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_SORT_HPP_INCLUDED
#define BOOST_MPL_SORT_HPP_INCLUDED

#include "boost/mpl/sort_fwd.hpp"
#include "boost/mpl/aux_/sort_impl.hpp"
#include "boost/mpl/lambda.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN

template < typename Sequence, typename Predicate >  // see sort_fwd.hpp
struct sort
{
private:
    typedef typename lambda<Predicate>::type pred_;

public:
    typedef typename sort_traits<
          typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence)
        >::template algorithm<
          Sequence, pred_
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,sort,(Sequence,Predicate))
};

BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SORT_HPP_INCLUDED
