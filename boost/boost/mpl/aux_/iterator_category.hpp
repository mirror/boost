//-----------------------------------------------------------------------------
// boost mpl/aux_/iterator_category.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ITERATOR_CATEGORY_HPP_INCLUDED
#define BOOST_MPL_AUX_ITERATOR_CATEGORY_HPP_INCLUDED

#include "boost/mpl/aux_/config/internals.hpp"

#if defined(BOOST_MPL_INTERNALS_USE_ITERATOR_CATEGORY)

#   include "boost/mpl/iterator_category.hpp"
#   define BOOST_MPL_AUX_ITERATOR_CATEGORY(iter) iterator_category<iter>::type

#else

#   define BOOST_MPL_AUX_ITERATOR_CATEGORY(iter) iter::category

#endif

#endif // BOOST_MPL_AUX_ITERATOR_CATEGORY_HPP_INCLUDED
