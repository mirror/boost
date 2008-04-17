
// Copyright 2005-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#define HASH_NAMESPACE boost
#define BOOST_HASH_NO_EXTENSIONS
#include <boost/functional/hash.hpp>
#include <boost/assert.hpp>

extern int f(std::size_t, int*);

int test_main(int, char**) {
    HASH_NAMESPACE::hash<int*> ptr_hasher;
    int x = 55;

    BOOST_ASSERT(!f(ptr_hasher(&x), &x));
    return 0;
}
