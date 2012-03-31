
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/scope_exit.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/config.hpp>
#include <boost/detail/lightweight_test.hpp>

#define SCOPE_EXIT_INC_DEC(variable, offset) \
    BOOST_SCOPE_EXIT_ID( \
            BOOST_PP_CAT(inc, __LINE__) /* unique ID */, 0 /* no TPL */, \
            (&variable) (offset) ) { \
        variable += offset; \
    } BOOST_SCOPE_EXIT_END_ID(BOOST_PP_CAT(inc, __LINE__)) \
    \
    BOOST_SCOPE_EXIT_ID( \
            BOOST_PP_CAT(dec, __LINE__) /* unique ID */, 0 /* no TPL */, \
            (&variable) (offset) ) { \
        variable -= offset; \
    } BOOST_SCOPE_EXIT_END_ID(BOOST_PP_CAT(dec, __LINE__))

#define SCOPE_EXIT_ALL_INC_DEC(variable, offset) \
    BOOST_SCOPE_EXIT_ALL_ID(BOOST_PP_CAT(inc, __LINE__) /* unique ID */, \
            (=) (&variable) ) { \
        variable += offset; \
    }; \
    BOOST_SCOPE_EXIT_ALL_ID(BOOST_PP_CAT(dec, __LINE__) /* unique ID */, \
            (=) (&variable) ) { \
        variable -= offset; \
    };

int main(void) {
    int x = 0, delta = 10;

    {
        SCOPE_EXIT_INC_DEC(x, delta)
    }
    BOOST_TEST(x == 0);

#ifndef BOOST_NO_LAMBDAS
    {
        SCOPE_EXIT_ALL_INC_DEC(x, delta)
    }
    BOOST_TEST(x == 0);
#endif // lambdas

    return boost::report_errors();
}

