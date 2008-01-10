
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include "../objects/test.hpp"
#include "../helpers/random_values.hpp"
#include "../helpers/tracker.hpp"
#include "../helpers/equivalent.hpp"
#include "../helpers/invariants.hpp"

test::seed_t seed(9063);

template <class T>
void copy_construct_tests1(T* = 0)
{
    BOOST_DEDUCED_TYPENAME T::hasher hf;
    BOOST_DEDUCED_TYPENAME T::key_equal eq;
    BOOST_DEDUCED_TYPENAME T::allocator_type al;

    {
        T x;
        T y(x);
        BOOST_TEST(y.empty());
        BOOST_TEST(test::equivalent(y.hash_function(), hf));
        BOOST_TEST(test::equivalent(y.key_eq(), eq));
        BOOST_TEST(test::equivalent(y.get_allocator(), al));
        BOOST_TEST(x.max_load_factor() == y.max_load_factor());
        test::check_equivalent_keys(y);
    }

    {
        test::random_values<T> v(1000);

        T x(v.begin(), v.end());
        T y(x);
        test::unordered_equivalence_tester<T> equivalent(x);
        equivalent(y);
        test::check_equivalent_keys(y);
    }

    {
        // In this test I drop the original containers max load factor, so it
        // is much lower than the load factor. The hash table is not allowed
        // to rehash, but the destination container should probably allocate
        // enough buckets to decrease the load factor appropriately.
        test::random_values<T> v(1000);
        T x(v.begin(), v.end());
        x.max_load_factor(x.load_factor() / 4);
        T y(x);
        test::unordered_equivalence_tester<T> equivalent(x);
        equivalent(y);
        // This isn't guaranteed:
        BOOST_TEST(y.load_factor() < y.max_load_factor());
        test::check_equivalent_keys(y);
    }
}

template <class T>
void copy_construct_tests2(T* ptr = 0)
{
    copy_construct_tests1(ptr);

    BOOST_DEDUCED_TYPENAME T::hasher hf(1);
    BOOST_DEDUCED_TYPENAME T::key_equal eq(1);
    BOOST_DEDUCED_TYPENAME T::allocator_type al(1);

    {
        T x(10000, hf, eq, al);
        T y(x);
        BOOST_TEST(y.empty());
        BOOST_TEST(test::equivalent(y.hash_function(), hf));
        BOOST_TEST(test::equivalent(y.key_eq(), eq));
        BOOST_TEST(test::equivalent(y.get_allocator(), al));
        BOOST_TEST(x.max_load_factor() == y.max_load_factor());
        test::check_equivalent_keys(y);
    }

    {
        test::random_values<T> v(1000);

        T x(v.begin(), v.end(), 0, hf, eq, al);
        T y(x);
        test::unordered_equivalence_tester<T> equivalent(x);
        equivalent(y);
        test::check_equivalent_keys(y);
    }
}

int main()
{
    copy_construct_tests1((boost::unordered_set<int>*) 0);
    copy_construct_tests1((boost::unordered_multiset<int>*) 0);
    copy_construct_tests1((boost::unordered_map<int, int>*) 0);
    copy_construct_tests1((boost::unordered_multimap<int, int>*) 0);

    copy_construct_tests2((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    copy_construct_tests2((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    copy_construct_tests2((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    copy_construct_tests2((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    copy_construct_tests2((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    copy_construct_tests2((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    copy_construct_tests2((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    copy_construct_tests2((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    return boost::report_errors();
}
