
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_EXTENSIONS
#  ifdef TEST_STD_INCLUDES
#    include <functional>
#  else
#    include <boost/functional/hash/hash.hpp>
#  endif
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#ifdef TEST_EXTENSIONS

BOOST_AUTO_UNIT_TEST(empty_array_test)
{
    int array[0];
    boost::hash<int[0]> hasher;
    BOOST_CHECK(hasher(array) == boost::hash_range(array, array));
    BOOST_CHECK(hasher((int*) 0) == boost::hash_range((int*) 0, (int*) 0));
}

#endif // TEST_EXTENSIONS


