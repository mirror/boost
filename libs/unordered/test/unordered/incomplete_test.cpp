
// Copyright 2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

namespace test
{
    struct value;
    struct hash;
    struct equals;
    template <class T>
    struct malloc_allocator;
    
    typedef boost::unordered_map<value, value, hash, equals, malloc_allocator<std::pair<value const, value> > > map;
    typedef boost::unordered_multimap<value, value, hash, equals, malloc_allocator<std::pair<value const, value> > > multimap;
    typedef boost::unordered_set<value, hash, equals, malloc_allocator<value> > set;
    typedef boost::unordered_multiset<value, hash, equals, malloc_allocator<value> > multiset;
    
    struct value {};
    struct hash { std::size_t operator()(value const&) const { return 0; } };
    struct equals { bool operator()(value const&, value const&) const { return true; } };
}

#include "../helpers/allocator.hpp"

int main() {
    test::map m1;
    test::multimap m2;
    test::set s1;
    test::multiset s2;
    
    m1[test::value()] = test::value();
    m2.insert(std::make_pair(test::value(), test::value()));
    s1.insert(test::value());
    s2.insert(test::value());
}
