
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <boost/scope_exit.hpp>
#include <boost/preprocessor/cat.hpp>
#define BOOST_TEST_MODULE TestSameLine
#include <boost/test/unit_test.hpp>

//[same_line
#define SCOPE_EXIT_INC_DEC(variable, offset) \
    BOOST_SCOPE_EXIT_ID( \
            BOOST_PP_CAT(inc, __LINE__) /* unique ID */, 0 /* no TPL */, \
            &variable, offset) { \
        variable += offset; \
    } BOOST_SCOPE_EXIT_END_ID(BOOST_PP_CAT(inc, __LINE__)) \
    \
    BOOST_SCOPE_EXIT_ID( \
            BOOST_PP_CAT(dec, __LINE__) /* unique ID */, 0 /* no TPL */, \
            &variable, offset) { \
        variable -= offset; \
    } BOOST_SCOPE_EXIT_END_ID(BOOST_PP_CAT(dec, __LINE__))

#define SCOPE_EXIT_ALL_INC_DEC(variable, offset) \
    BOOST_SCOPE_EXIT_ALL_ID(BOOST_PP_CAT(inc, __LINE__) /* unique ID */, \
            =, &variable) { \
        variable += offset; \
    }; \
    BOOST_SCOPE_EXIT_ALL_ID(BOOST_PP_CAT(dec, __LINE__) /* unique ID */, \
            =, &variable) { \
        variable -= offset; \
    };

BOOST_AUTO_TEST_CASE(test_same_line) {
    int x = 0, delta = 10;

    {
        SCOPE_EXIT_INC_DEC(x, delta) // Multiple scope exits on same line.
    }
    BOOST_CHECK(x == 0);

#ifndef BOOST_NO_LAMBDAS
    {
        SCOPE_EXIT_ALL_INC_DEC(x, delta) // Multiple scope exits on same line.
    }
    BOOST_CHECK(x == 0);
#endif
}
//]

#else

int main(void) { return 0; } // Trivial test.

#endif

