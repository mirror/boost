
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
#include "../helpers/input_iterator.hpp"
#include "../helpers/invariants.hpp"

#include <iostream>

test::seed_t seed(356730);

template <class T>
void constructor_tests1(T* = 0)
{
    BOOST_DEDUCED_TYPENAME T::hasher hf;
    BOOST_DEDUCED_TYPENAME T::key_equal eq;
    BOOST_DEDUCED_TYPENAME T::allocator_type al;

    std::cerr<<"Construct 1\n";
    {
        T x(0, hf, eq);
        BOOST_TEST(x.empty());
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 2\n";
    {
        T x(100, hf);
        BOOST_TEST(x.empty());
        BOOST_TEST(x.bucket_count() >= 100);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 3\n";
    {
        T x(2000);
        BOOST_TEST(x.empty());
        BOOST_TEST(x.bucket_count() >= 2000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 4\n";
    {
        T x;
        BOOST_TEST(x.empty());
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 5\n";
    {
        test::random_values<T> v(1000);
        T x(v.begin(), v.end(), 10000, hf, eq);
        BOOST_TEST(x.bucket_count() >= 10000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 6\n";
    {
        test::random_values<T> v(10);
        T x(v.begin(), v.end(), 10000, hf);
        BOOST_TEST(x.bucket_count() >= 10000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 7\n";
    {
        test::random_values<T> v(100);
        T x(v.begin(), v.end(), 100);
        BOOST_TEST(x.bucket_count() >= 100);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 8\n";
    {
        test::random_values<T> v(1);
        T x(v.begin(), v.end());
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 9\n";
    {
        T x(0, hf, eq, al);
        BOOST_TEST(x.empty());
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 10\n";
    {
        test::random_values<T> v(1000);
        T x(v.begin(), v.end(), 10000, hf, eq, al);
        BOOST_TEST(x.bucket_count() >= 10000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }
}

template <class T>
void constructor_tests2(T* = 0)
{
    BOOST_DEDUCED_TYPENAME T::hasher hf;
    BOOST_DEDUCED_TYPENAME T::hasher hf1(1);
    BOOST_DEDUCED_TYPENAME T::hasher hf2(2);
    BOOST_DEDUCED_TYPENAME T::key_equal eq;
    BOOST_DEDUCED_TYPENAME T::key_equal eq1(1);
    BOOST_DEDUCED_TYPENAME T::key_equal eq2(2);
    BOOST_DEDUCED_TYPENAME T::allocator_type al;
    BOOST_DEDUCED_TYPENAME T::allocator_type al1(1);
    BOOST_DEDUCED_TYPENAME T::allocator_type al2(2);

    std::cerr<<"Construct 1\n";
    {
        T x(10000, hf1, eq1);
        BOOST_TEST(x.bucket_count() >= 10000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf1));
        BOOST_TEST(test::equivalent(x.key_eq(), eq1));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 2\n";
    {
        T x(100, hf1);
        BOOST_TEST(x.empty());
        BOOST_TEST(x.bucket_count() >= 100);
        BOOST_TEST(test::equivalent(x.hash_function(), hf1));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 3\n";
    {
        test::random_values<T> v(100);
        T x(v.begin(), v.end(), 0, hf1, eq1);
        BOOST_TEST(test::equivalent(x.hash_function(), hf1));
        BOOST_TEST(test::equivalent(x.key_eq(), eq1));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"Construct 4\n";
    {
        test::random_values<T> v(5);
        T x(v.begin(), v.end(), 1000, hf1);
        BOOST_TEST(x.bucket_count() >= 1000);
        BOOST_TEST(test::equivalent(x.hash_function(), hf1));
        BOOST_TEST(test::equivalent(x.key_eq(), eq));
        BOOST_TEST(test::equivalent(x.get_allocator(), al));
        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }


    std::cerr<<"Construct 5\n";
    {
        test::random_values<T> v(100);
        T x(v.begin(), v.end(), 0, hf, eq, al1);
        T y(x.begin(), x.end(), 0, hf1, eq1, al2);
        test::check_container(x, v);
        test::check_container(y, x);
        test::check_equivalent_keys(x);
        test::check_equivalent_keys(y);
    }

    std::cerr<<"Construct 6\n";
    {
        test::random_values<T> v(100);
        T x(v.begin(), v.end(), 0, hf1, eq1);
        T y(x.begin(), x.end(), 0, hf, eq);
        test::check_container(x, v);
        test::check_container(y, x);
        test::check_equivalent_keys(x);
        test::check_equivalent_keys(y);
    }

    std::cerr<<"Construct 7\n";
    {
        test::random_values<T> v(100);
        T x(v.begin(), v.end(), 0, hf1, eq1);
        T y(x.begin(), x.end(), 0, hf2, eq2);
        test::check_container(x, v);
        test::check_container(y, x);
        test::check_equivalent_keys(x);
        test::check_equivalent_keys(y);
    }

    std::cerr<<"Construct 8 - from input iterator\n";
    {
        test::random_values<T> v(100);
        T x(test::input_iterator(v.begin()), test::input_iterator(v.end()), 0, hf1, eq1);
        T y(test::input_iterator(x.begin()), test::input_iterator(x.end()), 0, hf2, eq2);
        test::check_container(x, v);
        test::check_container(y, x);
        test::check_equivalent_keys(x);
        test::check_equivalent_keys(y);
    }
}

template <class T>
void map_constructor_test(T* = 0)
{
    std::cerr<<"map_constructor_test\n";

    typedef std::list<std::pair<BOOST_DEDUCED_TYPENAME T::key_type, BOOST_DEDUCED_TYPENAME T::mapped_type> > list;
    test::random_values<T> v(1000);
    list l;
    std::copy(v.begin(), v.end(), std::back_inserter(l));

    T x(l.begin(), l.end());

    test::check_container(x, v);
    test::check_equivalent_keys(x);
}

int main()
{
    std::cerr<<"Test1 unordered_set<int>\n";
    constructor_tests1((boost::unordered_set<int>*) 0);
    std::cerr<<"Test1 unordered_multiset<int>\n";
    constructor_tests1((boost::unordered_multiset<int>*) 0);
    std::cerr<<"Test1 unordered_map<int, int>\n";
    constructor_tests1((boost::unordered_map<int, int>*) 0);
    std::cerr<<"Test1 unordered_multimap<int, int>\n";
    constructor_tests1((boost::unordered_multimap<int, int>*) 0);

    std::cerr<<"Test1 unordered_set<test::object>\n";
    constructor_tests1((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test1 unordered_multiset<test::object>\n";
    constructor_tests1((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test1 unordered_map<test::object, test::object>\n";
    constructor_tests1((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test1 unordered_multimap<test::object, test::object>\n";
    constructor_tests1((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    std::cerr<<"Test1 unordered_set<test::equivalent_object>\n";
    constructor_tests1((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test1 unordered_multiset<test::equivalent_object>\n";
    constructor_tests1((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test1 unordered_map<test::equivalent_object, test::equivalent_object>\n";
    constructor_tests1((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test1 unordered_multimap<test::equivalent_object, test::equivalent_object>\n";
    constructor_tests1((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    std::cerr<<"Test2 unordered_set<test::object>\n";
    constructor_tests2((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test2 unordered_multiset<test::object>\n";
    constructor_tests2((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test2 unordered_map<test::object, test::object>\n";
    constructor_tests2((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Test2 unordered_multimap<test::object, test::object>\n";
    constructor_tests2((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    std::cerr<<"Test2 unordered_set<test::equivalent_object>\n";
    constructor_tests2((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test2 unordered_multiset<test::equivalent_object>\n";
    constructor_tests2((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test2 unordered_map<test::equivalent_object, test::equivalent_object>\n";
    constructor_tests2((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"Test2 unordered_multimap<test::equivalent_object, test::equivalent_object>\n";
    constructor_tests2((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    std::cerr<<"Map Test unordered_map<test::object, test::object>\n";
    map_constructor_test((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"Map Test unordered_multimap<test::object, test::object>\n";
    map_constructor_test((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    return boost::report_errors();
}
