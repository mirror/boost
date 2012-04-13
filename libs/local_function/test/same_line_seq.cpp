
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#include <boost/local_function.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <iostream>
    
#define LOCAL_INC_DEC(offset) \
    int BOOST_LOCAL_FUNCTION_ID( \
            BOOST_PP_CAT(inc, __LINE__) /* unique ID */, 0 /* no TPL */, \
            (const bind offset) (const int x) ) { \
        return x + offset; \
    } BOOST_LOCAL_FUNCTION_NAME(inc) \
    \
    int BOOST_LOCAL_FUNCTION_ID( \
            BOOST_PP_CAT(dec, __LINE__) /* unique ID */, 0 /* no TPL */, \
            (const bind offset) (const int x) ) { \
        return x - offset; \
    } BOOST_LOCAL_FUNCTION_NAME(dec)

#define LOCAL_INC_DEC_TPL(offset) \
    int BOOST_LOCAL_FUNCTION_TPL_ID(BOOST_PP_CAT(inc, __LINE__), \
            (const bind offset) (const int x) ) { \
        return x + offset; \
    } BOOST_LOCAL_FUNCTION_NAME(inc) \
    \
    int BOOST_LOCAL_FUNCTION_TPL_ID(BOOST_PP_CAT(dec, __LINE__), \
            (const bind offset) (const int x) ) { \
        return x - offset; \
    } BOOST_LOCAL_FUNCTION_NAME(dec)

template<typename T>
void f(int delta) {
    LOCAL_INC_DEC_TPL(delta) // Multiple local functions on same line.
    /** @todo back to BOOST_TEST(dec(inc(123)) == 123)) and doc that on vacpp compiler composition doesn't work */
    BOOST_TEST(inc(123) == 123 + delta);
    BOOST_TEST(dec(123) == 123 - delta);
}

int main(void) {
    int delta = 10;

    LOCAL_INC_DEC(delta) // Declare local functions on same line using `_ID`.
    /** @todo back to BOOST_TEST(dec(inc(123)) == 123)) and doc that on vacpp compiler composition doesn't work */
    BOOST_TEST(inc(123) == 123 + delta);
    BOOST_TEST(dec(123) == 123 - delta);

    f(delta);
    return boost::report_errors();
}

