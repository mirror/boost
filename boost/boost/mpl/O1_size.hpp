//-----------------------------------------------------------------------------
// boost mpl/O1_size.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_O1_SIZE_HPP_INCLUDED
#define BOOST_MPL_O1_SIZE_HPP_INCLUDED

#include "boost/mpl/O1_size_fwd.hpp"
#include "boost/mpl/aux_/O1_size_impl.hpp"
#include "boost/mpl/aux_/sequence_tag.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

// returns sequence size if it's an O(1) operation; otherwise returns -1
template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Sequence)
    >
struct O1_size
    : O1_size_traits< typename BOOST_MPL_AUX_SEQUENCE_TAG(Sequence) >
        ::template algorithm< Sequence >
{
};

BOOST_MPL_AUX_VOID_SPEC(1, O1_size)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_O1_SIZE_HPP_INCLUDED
