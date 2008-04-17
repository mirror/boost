
// Copyright 2005-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_EXTENSIONS
#  ifdef TEST_STD_INCLUDES
#    include <functional>
#  else
#    include <boost/functional/hash.hpp>
#  endif
#endif

#include <boost/test/minimal.hpp>

#ifdef TEST_EXTENSIONS

#include <set>

using std::set;
#define CONTAINER_TYPE set
#include "./hash_set_test.hpp"

using std::multiset;
#define CONTAINER_TYPE multiset
#include "./hash_set_test.hpp"

#endif

int test_main(int, char**)
{
#ifdef TEST_EXTENSIONS
    set_tests::set_hash_integer_tests();
    multiset_tests::multiset_hash_integer_tests();
#endif

    return 0;
}
