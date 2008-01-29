///////////////////////////////////////////////////////////////////////////////
// make_expr.hpp
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;
using namespace proto;

template<typename E> struct ewrap;

struct mydomain
  : domain<generator<ewrap> >
{};

template<typename E> struct ewrap
  : extends<E, ewrap<E>, mydomain>
{
    explicit ewrap(E const &e = E())
      : extends<E, ewrap<E>, mydomain>(e)
    {}
};

void test_make_expr()
{
    int i = 42;
    terminal<int const &>::type t1 = make_expr<tag::terminal>(1);
    terminal<int &>::type t2 = make_expr<tag::terminal>(i);
    posit<terminal<int const &>::type>::type p1 = make_expr<tag::posit>(1);
    posit<terminal<int &>::type>::type p2 = make_expr<tag::posit>(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = make_expr<tag::posit, mydomain>(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> const> // BUGBUG the const is an error here
      , ewrap<terminal<int const &>::type>
    >::type> p4 = make_expr<tag::plus>(p3, 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_make_expr2()
{
    int i = 42;
    terminal<int const &>::type t1 = functional::make_expr<tag::terminal>()(1);
    terminal<int &>::type t2 = functional::make_expr<tag::terminal>()(i);
    posit<terminal<int const &>::type>::type p1 = functional::make_expr<tag::posit>()(1);
    posit<terminal<int &>::type>::type p2 = functional::make_expr<tag::posit>()(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = functional::make_expr<tag::posit, mydomain>()(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> const> // BUGBUG the const is an error here
      , ewrap<terminal<int const &>::type>
    >::type> p4 = functional::make_expr<tag::plus, mydomain>()(p3, 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_unpack_expr()
{
    int i = 42;
    fusion::vector<int> v1(1);
    fusion::vector<int&> v2(i);
    terminal<int const &>::type t1 = unpack_expr<tag::terminal>(v1);
    terminal<int &>::type t2 = unpack_expr<tag::terminal>(v2);
    posit<terminal<int const &>::type>::type p1 = unpack_expr<tag::posit>(v1);
    posit<terminal<int &>::type>::type p2 = unpack_expr<tag::posit>(v2);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = unpack_expr<tag::posit, mydomain>(v2);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    fusion::vector<ewrap<posit<ewrap<terminal<int &>::type> >::type> &, int> v3(p3, 0);
    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int const &>::type>
    >::type> p4 = unpack_expr<tag::plus>(v3);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_unpack_expr2()
{
    int i = 42;
    fusion::vector<int> v1(1);
    fusion::vector<int&> v2(i);
    terminal<int const &>::type t1 = functional::unpack_expr<tag::terminal>()(v1);
    terminal<int &>::type t2 = functional::unpack_expr<tag::terminal>()(v2);
    posit<terminal<int const &>::type>::type p1 = functional::unpack_expr<tag::posit>()(v1);
    posit<terminal<int &>::type>::type p2 = functional::unpack_expr<tag::posit>()(v2);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = functional::unpack_expr<tag::posit, mydomain>()(v2);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    fusion::vector<ewrap<posit<ewrap<terminal<int &>::type> >::type> &, int> v3(p3, 0);
    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int const &>::type>
    >::type> p4 = functional::unpack_expr<tag::plus>()(v3);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test make_expr, unpack_expr and friends");

    test->add(BOOST_TEST_CASE(&test_make_expr));
    test->add(BOOST_TEST_CASE(&test_make_expr2));
    test->add(BOOST_TEST_CASE(&test_unpack_expr));
    test->add(BOOST_TEST_CASE(&test_unpack_expr2));

    return test;
}
