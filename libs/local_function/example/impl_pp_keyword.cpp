
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

//[impl_pp_keyword
#include <boost/local_function/detail/preprocessor/keyword/thisunderscore.hpp>
#include <boost/local_function/detail/preprocessor/keyword/const.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#define BOOST_TEST_MODULE TestImplPpKeyword
#include <boost/test/unit_test.hpp>

// Expand to 1 if space-separated tokens end with `this_`, 0 otherwise.
#define IS_THIS_BACK(tokens) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_THISUNDERSCORE_BACK( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_BIND_REMOVE_FRONT( \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_CONST_REMOVE_FRONT( \
        tokens \
    )))

BOOST_AUTO_TEST_CASE( test_impl_pp_keyword ) {
    BOOST_CHECK( IS_THIS_BACK(const bind this_) == 1 );
    BOOST_CHECK( IS_THIS_BACK(const bind& x) == 0 );
}
//]

