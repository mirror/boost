//-----------------------------------------------------------------------------
// boost mpl/aux_/fold_backward_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_FOLD_BACKWARD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_FOLD_BACKWARD_IMPL_HPP_INCLUDED

#include "boost/mpl/aux_/apply.hpp"
#include "boost/mpl/aux_/next.hpp"
#include "boost/mpl/aux_/config/eti.hpp"
#include "boost/config.hpp"

#if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && \
    !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include "boost/mpl/if.hpp"
#   include "boost/type_traits/is_same.hpp"
#endif

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if !defined(BOOST_MPL_NO_PREPROCESSED_HEADERS) && \
    !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER fold_backward_impl.hpp
#   include "boost/mpl/aux_/include_preprocessed.hpp"

#else

#   define BOOST_MPL_AUX_FOLD_IMPL_OP(iter) typename iter::type
#   define BOOST_MPL_AUX_FOLD_IMPL_NAME_PREFIX fold_backward
#   include "boost/mpl/aux_/fold_backward_impl_body.hpp"

#endif // BOOST_MPL_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_FOLD_BACKWARD_IMPL_HPP_INCLUDED
