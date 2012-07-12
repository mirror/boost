///////////////////////////////////////////////////////////////////////////////
// pack_expansion.hpp
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/proto/proto.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/typeof/typeof.hpp>

namespace mpl = boost::mpl;
namespace proto = boost::proto;
using proto::_;

template<typename T> T declval();

struct eval_ : proto::callable
{
    template<typename Sig>
    struct result;

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::plus, Left, Right)>
    {
        typedef BOOST_TYPEOF_TPL(declval<Left>() + declval<Right>()) type;
    };

    template<typename This, typename Left, typename Right>
    struct result<This(proto::tag::multiplies, Left, Right)>
    {
        typedef BOOST_TYPEOF_TPL(declval<Left>() * declval<Right>()) type;
    };

    template<typename Left, typename Right>
    typename result<eval_(proto::tag::plus, Left, Right)>::type
    operator()(proto::tag::plus, Left left, Right right) const
    {
        return left + right;
    }

    template<typename Left, typename Right>
    typename result<eval_(proto::tag::multiplies, Left, Right)>::type
    operator()(proto::tag::multiplies, Left left, Right right) const
    {
        return left * right;
    }
};

struct eval1
  : proto::or_<
        proto::when<proto::terminal<_>, proto::_value>
      , proto::otherwise<eval_(proto::tag_of<_>(), eval1(proto::pack(_))...)>
    >
{};

struct eval2
  : proto::or_<
        proto::when<proto::terminal<_>, proto::_value>
      , proto::otherwise<proto::call<eval_(proto::tag_of<_>(), eval2(proto::pack(_))...)> >
    >
{};

void test_call_pack()
{
    proto::terminal<int>::type i = {42};
    int res = eval1()(i + 2);
    BOOST_CHECK_EQUAL(res, 44);
    res = eval1()(i * 2);
    BOOST_CHECK_EQUAL(res, 84);
    res = eval1()(i * 2 + 4);
    BOOST_CHECK_EQUAL(res, 88);

    res = eval2()(i + 2);
    BOOST_CHECK_EQUAL(res, 44);
    res = eval2()(i * 2);
    BOOST_CHECK_EQUAL(res, 84);
    res = eval2()(i * 2 + 4);
    BOOST_CHECK_EQUAL(res, 88);
}

struct make_pair
  : proto::when<
        proto::binary_expr<_, proto::terminal<int>, proto::terminal<int> >
      , std::pair<int, int>(proto::_value(proto::pack(_))...)
    >
{};

void test_make_pack()
{
    proto::terminal<int>::type i = {42};
    std::pair<int, int> p = make_pair()(i + 43);
    BOOST_CHECK_EQUAL(p.first, 42);
    BOOST_CHECK_EQUAL(p.second, 43);
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test immediate evaluation of proto parse trees");

    test->add(BOOST_TEST_CASE(&test_call_pack));
    test->add(BOOST_TEST_CASE(&test_make_pack));

    return test;
}
