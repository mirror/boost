#ifndef BOOST_LIBS_PREPROCESSOR_TEST_TEST_HPP
#define BOOST_LIBS_PREPROCESSOR_TEST_TEST_HPP

// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

#include <boost/preprocessor/cat.hpp>

#define TEST(C) typedef BOOST_PP_CAT(test_,__LINE__)[((C)==1) ? 1 : -1];
#endif
