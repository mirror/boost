///////////////////////////////////////////////////////////////////////////////
// let.cpp
//
//  Copyright 2010 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <boost/proto/proto.hpp>
#include <boost/test/unit_test.hpp>

namespace mpl = boost::mpl;
namespace proto = boost::proto;
using proto::_;
using proto::_a;
using proto::_b;

///////////////////////////////////////////////////////////////////////////////
// test_let_call_once
//  verify that the transform bound to the local variable is really called
//  only once.
struct once
{
    static int ctors;
    once() { ++ctors; }
};

int once::ctors = 0;

struct LetCallOnce
  : proto::otherwise<
        proto::let<
            _a(once())
          , proto::functional::make_pair(_a, _a)
        >
    >
{};

void test_let_call_once()
{
    proto::literal<int> i(0);
    std::pair<once, once> p = LetCallOnce()(i);
    BOOST_CHECK_EQUAL(1, once::ctors);
}

///////////////////////////////////////////////////////////////////////////////
// test_let_object_transforms
//  verify that let works with object transforms.
struct LetObjectTransforms
  : proto::otherwise<
        proto::let<
            _a(int())
          , std::pair<_a, _a>(_a, _a)
        >
    >
{};

struct LetObjectTransforms2
  : proto::otherwise<
        proto::let<
            _a(int())
          , proto::make<std::pair<_a, _a>(_a, _a)>
        >
    >
{};

void test_let_object_transforms()
{
    proto::literal<int> i(0);
    std::pair<int, int> p = LetObjectTransforms()(i);
    BOOST_CHECK_EQUAL(0, p.first);
    BOOST_CHECK_EQUAL(0, p.second);

    std::pair<int, int> p2 = LetObjectTransforms2()(i);
    BOOST_CHECK_EQUAL(0, p2.first);
    BOOST_CHECK_EQUAL(0, p2.second);
}

///////////////////////////////////////////////////////////////////////////////
// test_let_data
//  verify that the monkeying with the data parameter is transparent.
struct MyData : proto::_data {};

struct LetData
  : proto::otherwise<
        proto::let<
            _a(int())
          , std::pair<MyData, _a>(MyData, _a)
        >
    >
{};

void test_let_data()
{
    std::string hello("hello");
    proto::literal<int> i(0);
    std::pair<std::string, int> p = LetData()(i, 0, hello);
    BOOST_CHECK_EQUAL(hello, p.first);
    BOOST_CHECK_EQUAL(0, p.second);
}

///////////////////////////////////////////////////////////////////////////////
// test_let_scope
//  verify that the local variables are scoped properly.
struct LetScope
  : proto::otherwise<
        proto::let<
            _a(proto::_value)
          , proto::functional::make_pair(
                _a
              , proto::let<
                    _a(proto::_state)
                  , proto::functional::make_pair(_a, proto::_data)
                >
            )
        >
    >
{};

void test_let_scope()
{
    std::string hello("hello");
    proto::literal<short> i((short)42);
    std::pair<short, std::pair<float, std::string> > p = LetScope()(i, 3.14f, hello);
    BOOST_CHECK_EQUAL(42, p.first);
    BOOST_CHECK_EQUAL(3.14f, p.second.first);
    BOOST_CHECK_EQUAL(hello, p.second.second);
}

///////////////////////////////////////////////////////////////////////////////
// test_let_scope2
//  verify that the local variables are scoped properly.
struct LetScope2
  : proto::otherwise<
        proto::let<
            _a(proto::_value)
          , proto::functional::make_pair(
                _a
              , proto::let<
                    _b(proto::_state)
                  , proto::functional::make_pair(_a, _b)
                >
            )
        >
    >
{};

struct LetScope3
  : proto::otherwise<
        proto::let<
            _a(proto::_value)
          , proto::functional::make_pair(
                _a
              , proto::let<
                    _b(proto::_state)
                  , proto::call<proto::functional::make_pair(_a, _b)>
                >
            )
        >
    >
{};

struct LetScope4
  : proto::otherwise<
        proto::let<
            _a(proto::_value)
          , proto::functional::make_pair(
                _a
              , proto::let<
                    _b(proto::_state)
                  , proto::call<proto::functional::make_pair>(_a, _b)
                >
            )
        >
    >
{};

void test_let_scope2()
{
    char const * sz = "";
    proto::literal<short> i((short)42);
    std::pair<short, std::pair<short, float> > p2 = LetScope2()(i, 3.14f, sz);
    BOOST_CHECK_EQUAL(42, p2.first);
    BOOST_CHECK_EQUAL(42, p2.second.first);
    BOOST_CHECK_EQUAL(3.14f, p2.second.second);

    std::pair<short, std::pair<short, float> > p3 = LetScope3()(i, 3.14f, sz);
    BOOST_CHECK_EQUAL(42, p3.first);
    BOOST_CHECK_EQUAL(42, p3.second.first);
    BOOST_CHECK_EQUAL(3.14f, p3.second.second);

    std::pair<short, std::pair<short, float> > p4 = LetScope4()(i, 3.14f, sz);
    BOOST_CHECK_EQUAL(42, p4.first);
    BOOST_CHECK_EQUAL(42, p4.second.first);
    BOOST_CHECK_EQUAL(3.14f, p4.second.second);
}

using namespace boost::unit_test;
///////////////////////////////////////////////////////////////////////////////
// init_unit_test_suite
//
test_suite* init_unit_test_suite( int argc, char* argv[] )
{
    test_suite *test = BOOST_TEST_SUITE("test let transform");

    test->add(BOOST_TEST_CASE(&test_let_call_once));
    test->add(BOOST_TEST_CASE(&test_let_object_transforms));
    test->add(BOOST_TEST_CASE(&test_let_data));
    test->add(BOOST_TEST_CASE(&test_let_scope));
    test->add(BOOST_TEST_CASE(&test_let_scope2));

    return test;
}
