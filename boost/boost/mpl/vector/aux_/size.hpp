//-----------------------------------------------------------------------------
// boost mpl/vector/aux_/size.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED

#include "boost/mpl/size_fwd.hpp"
#include "boost/mpl/integral_c.hpp"
#include "boost/mpl/vector/aux_/tag.hpp"
#include "boost/mpl/aux_/config/vector.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {

#if defined(BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL)

template<>
struct size_traits< aux::vector_tag >
{
    template< typename Vector > struct algorithm
        : Vector::size
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct size_traits< aux::vector_tag<N> >
{
    template< typename Vector > struct algorithm
        : integral_c<long,N>
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_TYPEOF_BASED_VECTOR_IMPL

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VECTOR_AUX_SIZE_HPP_INCLUDED
