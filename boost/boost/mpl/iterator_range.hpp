//-----------------------------------------------------------------------------
// boost mpl/iterator_range.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED

#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"

namespace boost {
namespace mpl {

struct iterator_range_tag;

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(First)
    , typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Last)
    >
struct iterator_range
{
    typedef iterator_range_tag tag;
    typedef iterator_range type;
    typedef First begin;
    typedef Last end;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,iterator_range,(First,Last))
};

BOOST_MPL_AUX_VOID_SPEC(2, iterator_range)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITERATOR_RANGE_HPP_INCLUDED
