//-----------------------------------------------------------------------------
// boost mpl/iterator_category.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED

#include "boost/mpl/aux_/void_spec.hpp"
#include "boost/mpl/aux_/lambda_support.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(Iterator)
    >
struct iterator_category
{
    typedef typename Iterator::category type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,iterator_category,(Iterator))
};

#if defined(BOOST_MPL_MSVC_60_ETI_BUG)
template<> struct iterator_category<int>
{
    typedef int type;
};
#endif

BOOST_MPL_AUX_VOID_SPEC(1, iterator_category)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_ITERATOR_CATEGORY_HPP_INCLUDED
