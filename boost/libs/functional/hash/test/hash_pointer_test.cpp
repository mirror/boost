//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash/hash.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include "./compile_time.hpp"

BOOST_AUTO_UNIT_TEST(pointer_tests)
{
    BOOST_CHECK(compile_time_tests<int*>::success);
    BOOST_CHECK(compile_time_tests<void*>::success);

    boost::hash<int*> x1;
    boost::hash<int*> x2;

    int int1;
    int int2;

    BOOST_CHECK_EQUAL(x1(0), x2(0));
    BOOST_CHECK_EQUAL(x1(&int1), x2(&int1));
    BOOST_CHECK_EQUAL(x1(&int2), x2(&int2));
}
