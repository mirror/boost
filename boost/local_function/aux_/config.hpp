
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CONFIG_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CONFIG_HPP_

#include <boost/config.hpp>

// PRIVATE //

// FUTURE: Replace this with BOOST_NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS after
// that macro is added to Boost.Config.
// If it is possible to pass local types (classes, etc) as template parameters.
// This is not possible in pure C++03 but it is possible in some C++03
// extensions (MSVC, GCC 4.5.x, etc).
#if !((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 4)) && \
        defined(__GXX_EXPERIMENTAL_CXX0X__)) && !defined(BOOST_MSVC)
    // Not GCC 4.5.x with -std=c++0x and not MSVC.
#   define BOOST_LOCAL_FUNCTION_AUX_CONFIG_NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS
#endif

// PUBLIC //

#ifdef BOOST_LOCAL_FUNCTION_AUX_CONFIG_NO_LOCAL_TYPES_AS_TEMPLATE_PARAMS
#   define BOOST_LOCAL_FUNCTION_AUX_CONFIG_LOCALS_AS_TPARAMS_01 0
#else
#   define BOOST_LOCAL_FUNCTION_AUX_CONFIG_LOCALS_AS_TPARAMS_01 1
#endif

#endif // #include guard

