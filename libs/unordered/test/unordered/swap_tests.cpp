
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>
#include <algorithm>
#include <iterator>
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include "../objects/test.hpp"
#include "../helpers/random_values.hpp"
#include "../helpers/tracker.hpp"
#include "../helpers/invariants.hpp"

test::seed_t seed(783472);

template <class X>
void swap_test_impl(X& x1, X& x2)
{
    test::ordered<X> tracker1 = test::create_ordered(x1);
    test::ordered<X> tracker2 = test::create_ordered(x2);
    tracker1.insert_range(x1.begin(), x1.end());
    tracker2.insert_range(x2.begin(), x2.end());
    x1.swap(x2);
    tracker1.compare(x2);
    tracker2.compare(x1);
}

template <class X>
void swap_tests1(X* = 0)
{
    {
        X x;
        swap_test_impl(x, x);
    }

    {
        X x,y;
        swap_test_impl(x, y);
    }

    {
        test::random_values<X> v(1000);
        X x, y(v.begin(), v.end());
        swap_test_impl(x, y);
        swap_test_impl(x, y);
    }

    {
        test::random_values<X> vx(1000), vy(1000);
        X x(vx.begin(), vx.end()), y(vy.begin(), vy.end());
        swap_test_impl(x, y);
        swap_test_impl(x, y);
    }
}

template <class X>
void swap_tests2(X* ptr = 0)
{
    swap_tests1(ptr);

    typedef BOOST_DEDUCED_TYPENAME X::hasher hasher;
    typedef BOOST_DEDUCED_TYPENAME X::key_equal key_equal;
    typedef BOOST_DEDUCED_TYPENAME X::allocator_type allocator_type;

    {
        X x(0, hasher(1), key_equal(1));
        X y(0, hasher(2), key_equal(2));
        swap_test_impl(x, y);
    }

    {
        test::random_values<X> v(1000);
        X x(v.begin(), v.end(), 0, hasher(1), key_equal(1));
        X y(0, hasher(2), key_equal(2));
        swap_test_impl(x, y);
    }

    {
        test::random_values<X> vx(100), vy(50);
        X x(vx.begin(), vx.end(), 0, hasher(1), key_equal(1));
        X y(vy.begin(), vy.end(), 0, hasher(2), key_equal(2));
        swap_test_impl(x, y);
        swap_test_impl(x, y);
    }

#if BOOST_UNORDERED_SWAP_METHOD == 1
    {
        test::random_values<X> vx(100), vy(50);
        X x(vx.begin(), vx.end(), 0, hasher(), key_equal(), allocator_type(1));
        X y(vy.begin(), vy.end(), 0, hasher(), key_equal(), allocator_type(2));
        try {
            swap_test_impl(x, y);
            BOOST_ERROR("Using swap method 1, swapping with unequal allocators didn't throw.");
        } catch (std::runtime_error) {}
    }
#else
    {
        test::random_values<X> vx(50), vy(100);
        X x(vx.begin(), vx.end(), 0, hasher(), key_equal(), allocator_type(1));
        X y(vy.begin(), vy.end(), 0, hasher(), key_equal(), allocator_type(2));
        swap_test_impl(x, y);
    }

    {
        test::random_values<X> vx(100), vy(100);
        X x(vx.begin(), vx.end(), 0, hasher(1), key_equal(1), allocator_type(1));
        X y(vy.begin(), vy.end(), 0, hasher(2), key_equal(2), allocator_type(2));
        swap_test_impl(x, y);
        swap_test_impl(x, y);
    }
#endif
}

int main()
{
    std::cerr<<"Erase unordered_set<int>.\n";
    swap_tests1((boost::unordered_set<int>*) 0);
    std::cerr<<"\nErase unordered_multiset<int>.\n";
    swap_tests1((boost::unordered_multiset<int>*) 0);
    std::cerr<<"\nErase unordered_map<int>.\n";
    swap_tests1((boost::unordered_map<int, int>*) 0);
    std::cerr<<"\nErase unordered_multimap<int>.\n";
    swap_tests1((boost::unordered_multimap<int, int>*) 0);

    std::cerr<<"\nErase unordered_set<test::object,..>.\n";
    swap_tests2((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_multiset<test::object,..>.\n";
    swap_tests2((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_map<test::object,..>.\n";
    swap_tests2((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_multimap<test::object,..>.\n";
    swap_tests2((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    return boost::report_errors();
}
