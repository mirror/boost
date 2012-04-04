
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_CONFIG_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_CONFIG_HPP_

#include <boost/config.hpp>

// PUBLIC //

// NOTE: If local classes can be passes as template parameters (always true for
// C++11 and true for some C++03 compilers like MSVC and old GCC versions),
// this library uses it to optimize local function performances (which in this
// case are comparable to C++11 lambdas).
#ifdef BOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS
#   define BOOST_LOCAL_FUNCTION_AUX_CONFIG_LOCALS_AS_TPARAMS_01 0
#   if __GNUC__
#       warning "Boost.LocalFunction: Local class template parameters"
#   elif BOOST_MSVC
#       pragma message("Boost.LocalFunction: Local class template parameters")
#   endif
#else
#   define BOOST_LOCAL_FUNCTION_AUX_CONFIG_LOCALS_AS_TPARAMS_01 1
#   if __GNUC__
#       warning "Boost.LocalFunction: No local class template parameters"
#   elif BOOST_MSVC
#       pragma message("Boost.LocalFunction: No local class template parameters")
#   endif
#endif

#endif // #include guard

