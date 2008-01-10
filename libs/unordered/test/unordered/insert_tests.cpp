
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/next_prior.hpp>
#include "../objects/test.hpp"
#include "../helpers/random_values.hpp"
#include "../helpers/tracker.hpp"
#include "../helpers/equivalent.hpp"
#include "../helpers/invariants.hpp"
#include "../helpers/input_iterator.hpp"

#include <iostream>
    
test::seed_t seed(243432);

template <class X>
void unique_insert_tests1(X* = 0)
{
    typedef BOOST_DEDUCED_TYPENAME X::iterator iterator;
    typedef test::ordered<X> ordered;

    std::cerr<<"insert(value) tests for containers with unique keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000);

    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {

        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        std::pair<iterator, bool> r1 = x.insert(*it);
        std::pair<BOOST_DEDUCED_TYPENAME ordered::iterator, bool> r2 = tracker.insert(*it);

        BOOST_TEST(r1.second == r2.second);
        BOOST_TEST(*r1.first == *r2.first);

        tracker.compare_key(x, *it);

        if(x.size() < b * old_bucket_count)
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

template <class X>
void equivalent_insert_tests1(X* = 0)
{
    std::cerr<<"insert(value) tests for containers with equivalent keys.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000);
    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {
        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        BOOST_DEDUCED_TYPENAME X::iterator r1 = x.insert(*it);
        BOOST_DEDUCED_TYPENAME test::ordered<X>::iterator r2 = tracker.insert(*it);

        BOOST_TEST(*r1 == *r2);

        tracker.compare_key(x, *it);

        if(x.size() < b * old_bucket_count)
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);
}

template <class X>
void insert_tests2(X* = 0)
{
    typedef BOOST_DEDUCED_TYPENAME test::ordered<X> tracker_type;
    typedef BOOST_DEDUCED_TYPENAME X::iterator iterator;
    typedef BOOST_DEDUCED_TYPENAME X::const_iterator const_iterator;
    typedef BOOST_DEDUCED_TYPENAME tracker_type::iterator tracker_iterator;

    std::cerr<<"insert(begin(), value) tests.\n";

    {
        X x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
                it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            iterator r1 = x.insert(x.begin(), *it);
            tracker_iterator r2 = tracker.insert(tracker.begin(), *it);
            BOOST_TEST(*r1 == *r2);
            tracker.compare_key(x, *it);

            if(x.size() < b * old_bucket_count)
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert(end(), value) tests.\n";

    {
        X x;
        X const& x_const = x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(100);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
                it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            const_iterator r1 = x.insert(x_const.end(), *it);
            tracker_iterator r2 = tracker.insert(tracker.end(), *it);
            BOOST_TEST(*r1 == *r2);
            tracker.compare_key(x, *it);

            if(x.size() < b * old_bucket_count)
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert(pos, value) tests.\n";

    {
        X x;
        const_iterator pos = x.begin();
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
                it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            pos = x.insert(pos, *it);
            tracker_iterator r2 = tracker.insert(tracker.begin(), *it);
            BOOST_TEST(*pos == *r2);
            tracker.compare_key(x, *it);

            if(x.size() < b * old_bucket_count)
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert single item range tests.\n";

    {
        X x;
        tracker_type tracker = test::create_ordered(x);

        test::random_values<X> v(1000);
        for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
                it != v.end(); ++it)
        {
            BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
            float b = x.max_load_factor();

            x.insert(it, boost::next(it));
            tracker.insert(*it);
            tracker.compare_key(x, *it);

            if(x.size() < b * old_bucket_count)
                BOOST_TEST(x.bucket_count() == old_bucket_count);
        }

        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert range tests.\n";

    {
        X x;

        test::random_values<X> v(1000);
        x.insert(v.begin(), v.end());

        test::check_container(x, v);
        test::check_equivalent_keys(x);
    }

    std::cerr<<"insert input iterator range tests.\n";

    {
        X x;

        test::random_values<X> v(1000);
        x.insert(test::input_iterator(v.begin()), test::input_iterator(v.end()));
        test::check_container(x, v);

        test::check_equivalent_keys(x);
    }
}

template <class X>
void map_tests(X* = 0)
{
    std::cerr<<"map tests.\n";

    X x;
    test::ordered<X> tracker = test::create_ordered(x);

    test::random_values<X> v(1000);
    for(BOOST_DEDUCED_TYPENAME test::random_values<X>::iterator it = v.begin();
            it != v.end(); ++it)
    {
        BOOST_DEDUCED_TYPENAME X::size_type old_bucket_count = x.bucket_count();
        float b = x.max_load_factor();

        x[it->first] = it->second;
        tracker[it->first] = it->second;

        tracker.compare_key(x, *it);

        if(x.size() < b * old_bucket_count)
            BOOST_TEST(x.bucket_count() == old_bucket_count);
    }

    test::check_equivalent_keys(x);   
}

template <class X>
void associative_insert_range_test(X* = 0)
{
    std::cerr<<"associative_insert_range_test\n";

    typedef std::list<std::pair<BOOST_DEDUCED_TYPENAME X::key_type, BOOST_DEDUCED_TYPENAME X::mapped_type> > list;
    test::random_values<X> v(1000);
    list l;
    std::copy(v.begin(), v.end(), std::back_inserter(l));

    X x; x.insert(l.begin(), l.end());

    test::check_equivalent_keys(x);
}

int main()
{
    unique_insert_tests1((boost::unordered_set<int>*) 0);
    equivalent_insert_tests1((boost::unordered_multiset<int>*) 0);
    unique_insert_tests1((boost::unordered_map<int, int>*) 0);
    equivalent_insert_tests1((boost::unordered_multimap<int, int>*) 0);

    unique_insert_tests1((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    equivalent_insert_tests1((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    unique_insert_tests1((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    equivalent_insert_tests1((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    unique_insert_tests1((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    equivalent_insert_tests1((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    unique_insert_tests1((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    equivalent_insert_tests1((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    insert_tests2((boost::unordered_set<int>*) 0);
    insert_tests2((boost::unordered_multiset<int>*) 0);
    insert_tests2((boost::unordered_map<int, int>*) 0);
    insert_tests2((boost::unordered_multimap<int, int>*) 0);

    insert_tests2((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    insert_tests2((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    insert_tests2((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    insert_tests2((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    insert_tests2((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    insert_tests2((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    insert_tests2((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    insert_tests2((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    map_tests((boost::unordered_map<int, int>*) 0);
    map_tests((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    map_tests((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    associative_insert_range_test((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    associative_insert_range_test((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    associative_insert_range_test((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    return boost::report_errors();
}
