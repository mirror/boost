//-----------------------------------------------------------------------------
// boost mpl/aux_/range_c/O1_size.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED

#include "boost/mpl/O1_size_fwd.hpp"
#include "boost/mpl/aux_/range_c/size.hpp"
#include "boost/mpl/aux_/range_c/tag.hpp"

namespace boost {
namespace mpl {

template<>
struct O1_size_traits< aux::half_open_range_tag >
    : size_traits< aux::half_open_range_tag >
{
};

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_RANGE_C_O1_SIZE_HPP_INCLUDED
