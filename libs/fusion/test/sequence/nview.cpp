/*=============================================================================
    Copyright (c) 2009 Hartmut Kaiser

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#include <boost/detail/lightweight_test.hpp>

#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/struct.hpp>
#include <boost/fusion/include/equal_to.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/nview.hpp>

#include <string>
#include <iostream>

struct test {
    int int_;
    std::string string_;
    double double_;
};

BOOST_FUSION_ADAPT_STRUCT(
    test, 
    (int, int_)
    (std::string, string_)
    (double, double_)
);

using namespace boost::fusion;

template <typename Sequence>
bool check_size(Sequence& s, int seqsize)
{
    return size(s) == seqsize;
}

template <typename Sequence, typename T>
bool check_deref_begin(Sequence& s, T val)
{
    return deref(begin(s)) == val;
}

template <typename Sequence, typename T>
bool check_deref_next(Sequence& s, T val)
{
    return deref(next(begin(s))) == val;
}

template <int N, typename Sequence, typename T>
bool check_deref_advance(Sequence& s, T val)
{
    return deref(advance_c<N>(begin(s))) == val;
}

template <typename Sequence, typename T>
bool check_deref_prior(Sequence& s, T val)
{
    return deref(prior(end(s))) == val;
}

template <int N, typename Sequence, typename T>
bool check_at(Sequence& s, T val)
{
    return at_c<N>(s) == val;
}

template <typename Sequence>
bool check_distance(Sequence& s, int val)
{
    return distance(begin(s), end(s)) == val;
}

int main()
{
    test t;
    t.int_ = 1;
    t.string_ = "test";
    t.double_ = 2.0;

    // check size()
    {
        BOOST_TEST(check_size(as_nview<0>(t), 1));
        BOOST_TEST(check_size(as_nview<2, 1>(t), 2));
        BOOST_TEST(check_size(as_nview<2, 1, 0>(t), 3));
        BOOST_TEST(check_size(as_nview<2, 1, 0, 2, 0>(t), 5));
    }

    // check deref/begin
    {
        BOOST_TEST(check_deref_begin(as_nview<0>(t), 1));
        BOOST_TEST(check_deref_begin(as_nview<2, 1>(t), 2.0));
        BOOST_TEST(check_deref_begin(as_nview<1, 2, 0>(t), "test"));
        BOOST_TEST(check_deref_begin(as_nview<2, 1, 0, 2, 0>(t), 2.0));
    }

    // check deref/next
    {
        BOOST_TEST(check_deref_next(as_nview<2, 1>(t), "test"));
        BOOST_TEST(check_deref_next(as_nview<1, 2, 0>(t), 2.0));
        BOOST_TEST(check_deref_next(as_nview<2, 0, 1, 2, 0>(t), 1));
    }

    // check deref/advance
    {
        BOOST_TEST(check_deref_advance<0>(as_nview<2, 1>(t), 2.0));
        BOOST_TEST(check_deref_advance<2>(as_nview<1, 2, 0>(t), 1));
        BOOST_TEST(check_deref_advance<4>(as_nview<2, 0, 1, 2, 0>(t), 1));
    }

    // check deref/prior
    {
        BOOST_TEST(check_deref_prior(as_nview<2, 1>(t), "test"));
        BOOST_TEST(check_deref_prior(as_nview<1, 2, 0>(t), 1));
        BOOST_TEST(check_deref_prior(as_nview<2, 0, 1, 2, 0>(t), 1));
    }

    // check at
    {
        BOOST_TEST(check_at<0>(as_nview<0>(t), 1));
        BOOST_TEST(check_at<1>(as_nview<2, 1>(t), "test"));
        BOOST_TEST(check_at<2>(as_nview<1, 2, 0>(t), 1));
        BOOST_TEST(check_at<4>(as_nview<2, 1, 0, 2, 0>(t), 1));
    }

    // check distance
    {
        BOOST_TEST(check_distance(as_nview<0>(t), 1));
        BOOST_TEST(check_distance(as_nview<2, 1>(t), 2));
        BOOST_TEST(check_distance(as_nview<1, 2, 0>(t), 3));
        BOOST_TEST(check_distance(as_nview<2, 1, 0, 2, 0>(t), 5));
    }

    return boost::report_errors();
}

