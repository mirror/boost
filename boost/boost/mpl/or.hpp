
#ifndef BOOST_MPL_OR_HPP_INCLUDED
#define BOOST_MPL_OR_HPP_INCLUDED

// + file: boost/mpl/or.hpp
// + last modified: 25/feb/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/config/use_preprocessed.hpp"

#if !defined(BOOST_MPL_NO_PREPROCESSED_HEADERS) \
 && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   include "boost/mpl/bool.hpp"
#   include "boost/mpl/aux_/nested_type_wknd.hpp"
#   include "boost/mpl/aux_/void_spec.hpp"
#   include "boost/mpl/aux_/lambda_support.hpp"

// agurt, 19/may/04: workaround a conflict with <iso646.h> header's 
// 'or' and 'and' macros, see http://tinyurl.com/3et69; 'defined(or)'
// has to be checked in a separate condition, otherwise GCC complains 
// about 'or' being an alternative token
#if defined(_MSC_VER)
#if defined(or)
#   pragma push_macro("or")
#   undef or
#   define or(x)
#endif
#endif

#   define BOOST_MPL_PREPROCESSED_HEADER or.hpp
#   include "boost/mpl/aux_/include_preprocessed.hpp"

#if defined(_MSC_VER) 
#if defined(or)
#   pragma pop_macro("or")
#endif
#endif

#else

#   define AUX_LOGICAL_OP_NAME or_
#   define AUX_LOGICAL_OP_VALUE1 true
#   define AUX_LOGICAL_OP_VALUE2 false
#   include "boost/mpl/aux_/logical_op.hpp"

#endif // BOOST_MPL_USE_PREPROCESSED_HEADERS
#endif // BOOST_MPL_OR_HPP_INCLUDED
