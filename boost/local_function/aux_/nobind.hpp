
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_NOBIND_HPP_

#include <boost/local_function/aux_/config.hpp>

// NOTE: The current implementation needs no-bind placeholders only when
// local types cannot be passed as template parameters.
#if !BOOST_LOCAL_FUNCTION_AUX_CONFIG_LOCALS_AS_TPARAMS_01

namespace boost { namespace local_function { namespace aux {

typedef int nobind_t; // Tag no-bind type.

nobind_t nobind; // Global variable so all no-binds can reference it.

} } } // namespace

#endif // locals as tparams

#endif // #include guard

