
// Copyright 2007-2008 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// All these headers are meant output a warning, but not cause the compilation
// to fail.

#include <boost/functional/hash/deque.hpp>
#include <boost/functional/hash/list.hpp>
#include <boost/functional/hash/map.hpp>
#include <boost/functional/hash/pair.hpp>
#include <boost/functional/hash/set.hpp>
#include <boost/functional/hash/vector.hpp>

// And a quick check that the hash library was included.
// Strictly speaking I should do this once for each header
// but that would just be wasting the testing resources.

#include <vector>

int main() {
    std::vector<int> v;
    boost::hash<std::vector<int> > x;
    x(v);
}
