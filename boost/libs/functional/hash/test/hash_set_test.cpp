
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_EXTENSIONS
#  ifdef TEST_STD_INCLUDES
#    include <functional>
#  else
#    include <boost/functional/hash/set.hpp>
#  endif
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#ifdef TEST_EXTENSIONS

#include <set>

using std::set;
#define CONTAINER_TYPE set
#include "./hash_set_test.hpp"

using std::multiset;
#define CONTAINER_TYPE multiset
#include "./hash_set_test.hpp"

#endif
