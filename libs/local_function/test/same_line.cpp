
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/config.hpp>
#ifndef BOOST_NO_VARIADIC_MACROS

#include <boost/local_function.hpp>
#include <boost/preprocessor/cat.hpp>
#define BOOST_TEST_MODULE TestSameLine
#include <boost/test/unit_test.hpp>
#include <iostream>
    
//[same_line
#define LOCAL_INC_DEC(offset) \
    int BOOST_LOCAL_FUNCTION_ID( \
            BOOST_PP_CAT(inc, __LINE__) /* unique ID */, 0 /* no TPL */, \
            const bind offset, const int x) { \
        return x + offset; \
    } BOOST_LOCAL_FUNCTION_NAME(inc) \
    \
    int BOOST_LOCAL_FUNCTION_ID( \
            BOOST_PP_CAT(dec, __LINE__) /* unique ID */, 0 /* no TPL */, \
            const bind offset, const int x) { \
        return x - offset; \
    } BOOST_LOCAL_FUNCTION_NAME(dec)

BOOST_AUTO_TEST_CASE(test_same_line)
{
    int delta = 10;
    LOCAL_INC_DEC(delta) // Declare local functions on same line using `_ID`.
    
    BOOST_CHECK(dec(inc(123)) == 123);
}
//]

#else

int main(void) { return 0; } // Trivial test.

#endif

