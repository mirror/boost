
// Copyright 2006-2007 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This test checks the runtime requirements of containers.

#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <algorithm>
#include "../helpers/equivalent.hpp"

template <class X>
void simple_test(X const& a)
{
    test::unordered_equivalence_tester<X> equivalent(a);

    {
        X u;
        BOOST_TEST(u.size() == 0);
        BOOST_TEST(X().size() == 0);
    }

    {
        BOOST_TEST(equivalent(X(a)));
    }

    {
        X u(a);
        BOOST_TEST(equivalent(u));
    }

    {
        X u = a;
        BOOST_TEST(equivalent(u));
    }

    {
        X b(a);
        BOOST_TEST(b.begin() == const_cast<X const&>(b).cbegin());
        BOOST_TEST(b.end() == const_cast<X const&>(b).cend());
    }

    {
        X b(a);
        X c;
        BOOST_TEST(equivalent(b));
        BOOST_TEST(c.empty());
        b.swap(c);
        BOOST_TEST(b.empty());
        BOOST_TEST(equivalent(c));
        b.swap(c);
        BOOST_TEST(b.empty());
        BOOST_TEST(equivalent(c));
    }

    {
        X u;
        X& r = u;
        BOOST_TEST(&(r = r) == &r);
        BOOST_TEST(r.empty());
        BOOST_TEST(&(r = a) == &r);
        BOOST_TEST(equivalent(r));
        BOOST_TEST(&(r = r) == &r);
        BOOST_TEST(equivalent(r));
    }

    {
        BOOST_TEST(a.size() ==
                (typename X::size_type) std::distance(a.begin(), a.end()));
    }

    {
        BOOST_TEST(a.empty() == (a.size() == 0));
    }

    {
        BOOST_TEST(a.empty() == (a.begin() == a.end()));
        X u;
        BOOST_TEST(u.begin() == u.end());
    }
}

int main()
{
    std::cout<<"Test unordered_set.\n";
    boost::unordered_set<int> set;
    simple_test(set);

    std::cout<<"Test unordered_multiset.\n";
    boost::unordered_multiset<int> multiset;
    simple_test(multiset);
    
    std::cout<<"Test unordered_map.\n";
    boost::unordered_map<int, int> map;
    simple_test(map);

    std::cout<<"Test unordered_multimap.\n";
    boost::unordered_multimap<int, int> multimap;
    simple_test(multimap);

    return boost::report_errors();
}
