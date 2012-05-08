
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>

// This test make sure that compilers for which local classes are expected to
// be valid template parameters indeed support such functionality.
// This feature is enabled by both BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
// and Boost.Config's BOOST_NO_LOCAL_CLASS_TEMPLATE_PARAMETERS. When supported,
// this feature is used to speed-up local function calls. This feature is
// supported by all standard C++11 compilers and some C++03 compilers as an
// extension (but not by the C++03 standard).
#if BOOST_LOCAL_FUNCTION_CONFIG_LOCALS_AS_TPARAMS
#   define LOCALS_AS_TPARAMS_TFUNC call_expected_to_pass
#   define LOCALS_AS_TPARAMS_TCLASS instantiation_expected_to_pass
#else
#   define LOCALS_AS_TPARAMS_TFUNC call_exptected_to_fail
#   define LOCALS_AS_TPARAMS_TCLASS instantiation_expected_to_fail
#endif

template<typename T> struct LOCALS_AS_TPARAMS_TCLASS { void use(void) {} };
template<typename T> void LOCALS_AS_TPARAMS_TFUNC(T) {}

int main(void) {
    struct local_class {} local_obj;
    LOCALS_AS_TPARAMS_TCLASS<local_class>().use();
    LOCALS_AS_TPARAMS_TFUNC(local_obj);
    return 0;
}

