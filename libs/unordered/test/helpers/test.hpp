
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_UNORDERED_TEST_TEST_HEADER)
#define BOOST_UNORDERED_TEST_TEST_HEADER

#if defined(BOOST_UNORDERED_USE_TEST)
#include <boost/test/test_tools.hpp>
#define UNORDERED_CHECK(x) BOOST_CHECK(x)
#define UNORDERED_REQUIRE(x) BOOST_REQUIRE(x)
#else
#include <boost/detail/lightweight_test.hpp>
#define UNORDERED_CHECK(x) BOOST_TEST(x)
#define UNORDERED_REQUIRE(x) if(!(x)) { BOOST_ERROR(BOOST_STRINGIZE(x)); throw test::lightweight::test_failure(); }
#endif

#endif
