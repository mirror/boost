//-----------------------------------------------------------------------------
// boost mpl/vector/aux_/tag.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED

#include "boost/mpl/aux_/config/vector.hpp"

namespace boost {
namespace mpl {
namespace aux {

#if defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL)
struct vector_tag;
#else
template< long N > struct vector_tag;
#endif

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_AUX_TAG_HPP_INCLUDED
