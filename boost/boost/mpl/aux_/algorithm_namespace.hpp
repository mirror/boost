//-----------------------------------------------------------------------------
// boost mpl/aux_/algorithm_namespace.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED
#define BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED

#if defined(__GNUC__) && __GNUC__ >= 3

#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX algo_::
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN namespace algo_ {
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END } using namespace algo_;

#else

#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_PREFIX /**/
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_BEGIN /**/
#   define BOOST_MPL_AUX_AGLORITHM_NAMESPACE_END /**/

#endif

#endif // BOOST_MPL_AUX_ALGORITHM_NAMESPACE_HPP_INCLUDED
