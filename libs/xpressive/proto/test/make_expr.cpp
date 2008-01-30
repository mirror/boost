///////////////////////////////////////////////////////////////////////////////
// make_expr.hpp
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <sstream>
#include <boost/xpressive/proto/proto.hpp>
#include <boost/xpressive/proto/transform.hpp>
#include <boost/fusion/tuple.hpp>
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
    terminal<int>::type t1 = make_expr<tag::terminal>(1);
    terminal<int>::type t2 = make_expr<tag::terminal>(i);
    posit<terminal<int>::type>::type p1 = make_expr<tag::posit>(1);
    posit<terminal<int>::type>::type p2 = make_expr<tag::posit>(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int>::type> >::type> p3 = make_expr<tag::posit, mydomain>(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        ewrap<posit<ewrap<terminal<int>::type> >::type>
      , ewrap<terminal<int>::type>
    >::type> p4 = make_expr<tag::plus>(p3, 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_make_expr_ref()
{
    int i = 42;
    terminal<int const &>::type t1 = make_expr<tag::terminal>(boost::cref(1)); // DANGEROUS
    terminal<int &>::type t2 = make_expr<tag::terminal>(boost::ref(i));
    BOOST_CHECK_EQUAL(&i, &proto::arg(t2));
    posit<terminal<int const &>::type>::type p1 = make_expr<tag::posit>(boost::cref(1)); // DANGEROUS
    posit<terminal<int &>::type>::type p2 = make_expr<tag::posit>(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = make_expr<tag::posit, mydomain>(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int>::type>
    >::type> p4 = make_expr<tag::plus>(boost::ref(p3), 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_make_expr_functional()
{
    int i = 42;
    terminal<int>::type t1 = functional::make_expr<tag::terminal>()(1);
    terminal<int>::type t2 = functional::make_expr<tag::terminal>()(i);
    posit<terminal<int>::type>::type p1 = functional::make_expr<tag::posit>()(1);
    posit<terminal<int>::type>::type p2 = functional::make_expr<tag::posit>()(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int>::type> >::type> p3 = functional::make_expr<tag::posit, mydomain>()(i);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        ewrap<posit<ewrap<terminal<int>::type> >::type>
      , ewrap<terminal<int>::type>
    >::type> p4 = functional::make_expr<tag::plus, mydomain>()(p3, 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_make_expr_functional_ref()
{
    int i = 42;
    terminal<int const &>::type t1 = functional::make_expr<tag::terminal>()(boost::cref(1)); // DANGEROUS
    terminal<int &>::type t2 = functional::make_expr<tag::terminal>()(boost::ref(i));
    BOOST_CHECK_EQUAL(&i, &proto::arg(t2));
    posit<terminal<int const &>::type>::type p1 = functional::make_expr<tag::posit>()(boost::cref(1)); // DANGEROUS
    posit<terminal<int &>::type>::type p2 = functional::make_expr<tag::posit>()(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = functional::make_expr<tag::posit, mydomain>()(boost::ref(i));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        proto::ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int>::type>
    >::type> p4 = functional::make_expr<tag::plus, mydomain>()(boost::ref(p3), 0);
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_unpack_expr()
{
    int i = 42;
    terminal<int>::type t1 = unpack_expr<tag::terminal>(fusion::make_tuple(1));
    terminal<int &>::type t2 = unpack_expr<tag::terminal>(fusion::make_tuple(boost::ref(i)));
    posit<terminal<int>::type>::type p1 = unpack_expr<tag::posit>(fusion::make_tuple(1));
    posit<terminal<int &>::type>::type p2 = unpack_expr<tag::posit>(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = unpack_expr<tag::posit, mydomain>(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int>::type>
    >::type> p4 = unpack_expr<tag::plus>(fusion::make_tuple(boost::ref(p3), 0));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

void test_unpack_expr_functional()
{
    int i = 42;
    terminal<int>::type t1 = functional::unpack_expr<tag::terminal>()(fusion::make_tuple(1));
    terminal<int &>::type t2 = functional::unpack_expr<tag::terminal>()(fusion::make_tuple(boost::ref(i)));
    posit<terminal<int>::type>::type p1 = functional::unpack_expr<tag::posit>()(fusion::make_tuple(1));
    posit<terminal<int &>::type>::type p2 = functional::unpack_expr<tag::posit>()(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p2)), 42);

    ewrap<posit<ewrap<terminal<int &>::type> >::type> p3 = functional::unpack_expr<tag::posit, mydomain>()(fusion::make_tuple(boost::ref(i)));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(p3)), 42);

    ewrap<plus<
        ref_<ewrap<posit<ewrap<terminal<int &>::type> >::type> >
      , ewrap<terminal<int>::type>
    >::type> p4 = functional::unpack_expr<tag::plus>()(fusion::make_tuple(boost::ref(p3), 0));
    BOOST_CHECK_EQUAL(proto::arg(proto::arg(proto::left(p4))), 42);
}

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#define _ref(x) call<_ref(x)>
#define Minus(x) call<Minus(x)>
#endif

// Turn all terminals held by reference into ones held by value
struct ByVal
  : or_<
        when<terminal<_>, _make_terminal(_arg)>
      , when<nary_expr<_, vararg<ByVal> > >
    >
{};

// Turn all terminals held by value into ones held by reference (not safe in general)
struct ByRef
  : or_<
        when<terminal<_>, _make_terminal(_ref(_arg))>
      , when<nary_expr<_, vararg<ByRef> > >
    >
{};

// turn all plus noded to minus nodes:
struct Minus
  : or_<
        when<terminal<_> >
      , when<plus<Minus, Minus>, _make_minus(Minus(_left), Minus(_right)) >
    >
{};

struct Square
  : or_<
        // Not creating new terminal nodes here,
        // so hold the existing terminals by reference:
        when<terminal<_>, _make_multiplies(_ref(_), _ref(_))>
      , when<plus<Square, Square> >
    >
{};

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
#undef _ref
#undef Minus
#endif

void test_make_expr_transform()
{
    int x = 0;
    plus< 
        terminal<int>::type
      , terminal<int>::type
    >::type t1 = ByVal()(as_expr(1) + 1, x, x);

    plus< 
        terminal<int const &>::type
      , terminal<int const &>::type
    >::type t2 = ByRef()(as_expr(1) + 1, x, x);

    minus<
        terminal<int>::type
      , terminal<int const &>::type
    >::type t3 = Minus()(as_expr(1) + 1, x, x);

    plus<
        multiplies<ref_<terminal<int>::type const>, ref_<terminal<int>::type const> >::type
      , multiplies<ref_<terminal<int const &>::type const>, ref_<terminal<int const &>::type const> >::type
    >::type t4 = Square()(as_expr(1) + 1, x, x);
}

using namespace unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test make_expr, unpack_expr and friends");

    test->add(BOOST_TEST_CASE(&test_make_expr));
    test->add(BOOST_TEST_CASE(&test_make_expr_ref));
    test->add(BOOST_TEST_CASE(&test_make_expr_functional));
    test->add(BOOST_TEST_CASE(&test_make_expr_functional_ref));
    test->add(BOOST_TEST_CASE(&test_unpack_expr));
    test->add(BOOST_TEST_CASE(&test_unpack_expr_functional));
    test->add(BOOST_TEST_CASE(&test_make_expr_transform));

    return test;
}
