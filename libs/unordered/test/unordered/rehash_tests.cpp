
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include "../helpers/random_values.hpp"
#include "../helpers/tracker.hpp"

test::seed_t seed(2974);

template <class X>
bool postcondition(X const& x, BOOST_DEDUCED_TYPENAME X::size_type n)
{
    return x.bucket_count() > x.size() / x.max_load_factor() && x.bucket_count() >= n;
}

template <class X>
void rehash_empty_test1(X* = 0)
{
    X x;

    x.rehash(10000);
    BOOST_TEST(postcondition(x, 10000));

    x.rehash(0);
    BOOST_TEST(postcondition(x, 0));
}

template <class X>
void rehash_test1(X* = 0)
{
    test::random_values<X> v(1000);
    test::ordered<X> tracker;
    tracker.insert_range(v.begin(), v.end());
    X x(v.begin(), v.end());

    x.rehash(0); BOOST_TEST(postcondition(x, 0));
    tracker.compare(x);

    x.max_load_factor(0.25);
    x.rehash(0); BOOST_TEST(postcondition(x, 0));
    tracker.compare(x);

    x.max_load_factor(50.0);
    x.rehash(0); BOOST_TEST(postcondition(x, 0));
    tracker.compare(x);

    x.rehash(1000); BOOST_TEST(postcondition(x, 1000));
    tracker.compare(x);
}

template <class X>
void rehash_tests(X* ptr = 0)
{
    rehash_empty_test1(ptr);
    rehash_test1(ptr);
}

int main() {
    rehash_tests((boost::unordered_set<int>*) 0);
    rehash_tests((boost::unordered_multiset<int>*) 0);
    rehash_tests((boost::unordered_map<int, int>*) 0);
    rehash_tests((boost::unordered_multimap<int, int>*) 0);

    return boost::report_errors();
}
