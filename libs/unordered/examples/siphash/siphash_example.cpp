
// Copyright 2012 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This is also released into the public domain.

#include <boost/unordered_set.hpp>
#include <cassert>
#include "siphash.hpp"

int main()
{
    boost::unordered_set<int, hash::siphash<int> > x1(0, hash::generate_sipkey());
    boost::unordered_set<int, hash::siphash<int> > x2(0, hash::generate_sipkey());

    assert(x1 == x2);

    x1.insert(10);
    x1.insert(30);
    x1.insert(50);
    assert(x1 != x2);

    x2.insert(100);
    assert(x1 != x2);

    x1.insert(x2.begin(), x2.end());
    x2.insert(x1.begin(), x1.end());
    assert(x1 == x2);

    assert(x1.bucket(10) != x2.bucket(10));
    assert(x1.bucket(30) != x2.bucket(30));

    x1 = x2;

    assert(x1.bucket(10) == x2.bucket(10));
    assert(x1.bucket(30) == x2.bucket(30));
}
