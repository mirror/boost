// Boost.Function library

//  Copyright Doug Gregor 2004. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#include <boost/test/minimal.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>

static int forty_two() { return 42; }

struct Seventeen
{
  int operator()() const { return 17; }
};

struct ReturnInt
{
  explicit ReturnInt(int value) : value(value) {}

  int operator()() const { return value; }

  int value;
};

bool operator==(const ReturnInt& x, const ReturnInt& y)
{ return x.value == y.value; }

bool operator!=(const ReturnInt& x, const ReturnInt& y)
{ return x.value != y.value; }

static void contains_test()
{
  boost::function0<int> f;

  f = &forty_two;
  BOOST_TEST(*f.contains<int (*)()>() == &forty_two);
  BOOST_TEST(!f.contains<Seventeen>());

  f = Seventeen();
  BOOST_TEST(!f.contains<int (*)()>());
  BOOST_TEST(f.contains<Seventeen>());

  Seventeen this_seventeen;
  f = boost::ref(this_seventeen);
  BOOST_TEST(!f.contains<int (*)()>());
  BOOST_TEST(f.contains<Seventeen>());
  BOOST_TEST(f.contains<Seventeen>() == &this_seventeen);
}

static void equal_test()
{
  boost::function0<int> f;

  f = &forty_two;
  BOOST_TEST(f == &forty_two);
  BOOST_TEST(&forty_two == f);
  BOOST_TEST(f != ReturnInt(17));
  BOOST_TEST(ReturnInt(17) != f);

  f = ReturnInt(17);
  BOOST_TEST(f != &forty_two);
  BOOST_TEST(&forty_two != f);
  BOOST_TEST(f == ReturnInt(17));
  BOOST_TEST(ReturnInt(17) == f);
  BOOST_TEST(f != ReturnInt(16));
  BOOST_TEST(ReturnInt(16) != f);

#if !defined(BOOST_FUNCTION_NO_FUNCTION_TYPE_SYNTAX)
  boost::function<int(void)> g;

  g = &forty_two;
  BOOST_TEST(g == &forty_two);
  BOOST_TEST(&forty_two == g);
  BOOST_TEST(g != ReturnInt(17));
  BOOST_TEST(ReturnInt(17) != g);

  g = ReturnInt(17);
  BOOST_TEST(g != &forty_two);
  BOOST_TEST(&forty_two != g);
  BOOST_TEST(g == ReturnInt(17));
  BOOST_TEST(ReturnInt(17) == g);
  BOOST_TEST(g != ReturnInt(16));
  BOOST_TEST(ReturnInt(16) != g);
#endif
}

int test_main(int, char*[])
{
  contains_test();
  equal_test();

  return 0;
}
