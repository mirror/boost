//-----------------------------------------------------------------------------
// boost mpl/single_view.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
#define BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED

#include "boost/mpl/aux_/single_element_iter.hpp"
#include "boost/mpl/iterator_range.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct single_view
    : iterator_range<
          aux::single_element_iter<T,0>
        , aux::single_element_iter<T,1>
        >
{
};

BOOST_MPL_AUX_VOID_SPEC(1, single_view)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_SINGLE_VIEW_HPP_INCLUDED
