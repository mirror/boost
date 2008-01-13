
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
#include "../helpers/helpers.hpp"

#include <iostream>

test::seed_t seed(85638);

template <class Container>
void erase_tests1(Container* = 0)
{
    std::cerr<<"Erase by key.\n";
    {
        test::random_values<Container> v(1000);
        Container x(v.begin(), v.end());
        for(BOOST_DEDUCED_TYPENAME test::random_values<Container>::iterator it = v.begin();
            it != v.end(); ++it)
        {
            std::size_t count = x.count(test::get_key<Container>(*it));
            std::size_t old_size = x.size();
            BOOST_TEST(count == x.erase(test::get_key<Container>(*it)));
            BOOST_TEST(x.size() == old_size - count);
            BOOST_TEST(x.count(test::get_key<Container>(*it)) == 0);
            BOOST_TEST(x.find(test::get_key<Container>(*it)) == x.end());
        }
    }

    std::cerr<<"erase(begin()).\n";
    {
        test::random_values<Container> v(1000);
        Container x(v.begin(), v.end());
        std::size_t size = x.size();
        while(size > 0 && !x.empty())
        {
            BOOST_DEDUCED_TYPENAME Container::key_type key = test::get_key<Container>(*x.begin());
            std::size_t count = x.count(key);
            BOOST_DEDUCED_TYPENAME Container::iterator pos = x.erase(x.begin());
            --size;
            BOOST_TEST(pos == x.begin());
            BOOST_TEST(x.count(key) == count - 1);
            BOOST_TEST(x.size() == size);
        }
        BOOST_TEST(x.empty());
    }

    std::cerr<<"erase(random position).\n";
    {
        test::random_values<Container> v(1000);
        Container x(v.begin(), v.end());
        std::size_t size = x.size();
        while(size > 0 && !x.empty())
        {
            using namespace std;
            int index = rand() % x.size();
            BOOST_DEDUCED_TYPENAME Container::const_iterator prev, pos, next;
            if(index == 0) {
                prev = pos = x.begin();
            }
            else {
                prev = boost::next(x.begin(), index - 1);
                pos = boost::next(prev);
            }
            next = boost::next(pos);
            BOOST_DEDUCED_TYPENAME Container::key_type key = test::get_key<Container>(*pos);
            std::size_t count = x.count(key);
            BOOST_TEST(next == x.erase(pos));
            --size;
            if(size > 0)
                BOOST_TEST(index == 0 ? next == x.begin() :
                        next == boost::next(prev));
            BOOST_TEST(x.count(key) == count - 1);
            BOOST_TEST(x.size() == size);
        }
        BOOST_TEST(x.empty());
    }

    std::cerr<<"erase(ranges).\n";
    {
        test::random_values<Container> v(500);
        Container x(v.begin(), v.end());

        std::size_t size = x.size();

        // I'm actually stretching it a little here, as the standard says it
        // returns 'the iterator immediately following the erase elements'
        // and if nothing is erased, then there's nothing to follow. But I
        // think this is the only sensible option...
        BOOST_TEST(x.erase(x.end(), x.end()) == x.end());
        BOOST_TEST(x.erase(x.begin(), x.begin()) == x.begin());
        BOOST_TEST(x.size() == size);

        BOOST_TEST(x.erase(x.begin(), x.end()) == x.end());
        BOOST_TEST(x.empty());
        BOOST_TEST(x.begin() == x.end());

        BOOST_TEST(x.erase(x.begin(), x.end()) == x.begin());
    }

    std::cerr<<"clear().\n";
    {
        test::random_values<Container> v(500);
        Container x(v.begin(), v.end());
        x.clear();
        BOOST_TEST(x.empty());
        BOOST_TEST(x.begin() == x.end());
    }
}

int main()
{
    std::cerr<<"Erase unordered_set<int>.\n";
    erase_tests1((boost::unordered_set<int>*) 0);
    std::cerr<<"\nErase unordered_multiset<int>.\n";
    erase_tests1((boost::unordered_multiset<int>*) 0);
    std::cerr<<"\nErase unordered_map<int>.\n";
    erase_tests1((boost::unordered_map<int, int>*) 0);
    std::cerr<<"\nErase unordered_multimap<int>.\n";
    erase_tests1((boost::unordered_multimap<int, int>*) 0);

    std::cerr<<"\nErase unordered_set<test::object,..>.\n";
    erase_tests1((boost::unordered_set<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_multiset<test::object,..>.\n";
    erase_tests1((boost::unordered_multiset<test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_map<test::object,..>.\n";
    erase_tests1((boost::unordered_map<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);
    std::cerr<<"\nErase unordered_multimap<test::object,..>.\n";
    erase_tests1((boost::unordered_multimap<test::object, test::object, test::hash, test::equal_to, test::allocator<test::object> >*) 0);

    std::cerr<<"\nErase unordered_set<test::equivalent_object,..>.\n";
    erase_tests1((boost::unordered_set<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"\nErase unordered_multiset<test::equivalent_object,..>.\n";
    erase_tests1((boost::unordered_multiset<test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"\nErase unordered_map<test::equivalent_object,..>.\n";
    erase_tests1((boost::unordered_map<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);
    std::cerr<<"\nErase unordered_multimap<test::equivalent_object,..>.\n";
    erase_tests1((boost::unordered_multimap<test::equivalent_object, test::equivalent_object, test::hash, test::equal_to, test::allocator<test::equivalent_object> >*) 0);

    return boost::report_errors();
}
