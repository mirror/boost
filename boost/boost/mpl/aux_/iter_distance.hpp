//-----------------------------------------------------------------------------
// boost mpl/aux_/iter_distance.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ITER_DISTANCE_HPP_INCLUDED
#define BOOST_MPL_AUX_ITER_DISTANCE_HPP_INCLUDED

#include "boost/mpl/aux_/iterator_names.hpp"
#include "boost/mpl/aux_/msvc_never_true.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {
namespace aux {

#if defined(BOOST_MSVC) && BOOST_MSVC < 1300

// msvc_distance
#define BOOST_MPL_AUX_MSVC_DTW_NAME msvc_distance
#define BOOST_MPL_AUX_MSVC_DTW_ORIGINAL_NAME BOOST_MPL_AUX_ITERATOR_DISTANCE
#define BOOST_MPL_AUX_MSVC_DTW_ARITY 1
#include "boost/mpl/aux_/msvc_dtw.hpp"

template<
      typename Iterator
    , typename Other
    > 
struct iter_distance
    : msvc_distance<Iterator>::template result_<Other>
{
};

#else

template<
      typename Iterator
    , typename Other
    > 
struct iter_distance
    : Iterator::template BOOST_MPL_AUX_ITERATOR_DISTANCE<Other>
{
};

#endif

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_ITER_DISTANCE_HPP_INCLUDED
