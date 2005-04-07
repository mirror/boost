
//  (C) Copyright Daniel James 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_EXTENSIONS
#  ifdef TEST_STD_INCLUDES
#    include <functional>
#  else
#    include <boost/functional/hash/map.hpp>
#  endif
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <map>

#ifdef TEST_EXTENSIONS

using std::map;
#define CONTAINER_TYPE map
#include "./hash_map_test.hpp"

using std::multimap;
#define CONTAINER_TYPE multimap
#include "./hash_map_test.hpp"

#endif // TEST_EXTENSTIONS
