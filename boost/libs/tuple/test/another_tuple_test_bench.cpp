//  tuple_test_bench.cpp  --------------------------------
//
// Defining any of E1 to E5 or E7 to E11 opens some illegal code that 
// should cause the compliation to fail.

#define BOOST_INCLUDE_MAIN  // for testing, include rather than link
#include <boost/test/test_tools.hpp>    // see "Header Implementation Option"

#include "boost/tuple/tuple.hpp"

#include "boost/tuple/tuple_comparison.hpp"

using namespace std;
using namespace boost;

class foo
{
public:
  explicit foo(int v) : val(v) {}

  bool operator==(const foo& other) const
  {
    return val == other.val;
  }

private:
  foo() {}
  int val;
};

void
construction_test()
{
  tuple<int> t1; 
  BOOST_TEST(get<0>(t1) == int());
  
  tuple<float> t2(5.5f);
  BOOST_TEST(get<0>(t2) == 5.5f);

  tuple<foo> t3(foo(12));
  BOOST_TEST(get<0>(t3) == foo(12));

  tuple<double> t4(t2);
  BOOST_TEST(get<0>(t4) == 5.5);

  tuple<int, float> t5;
  BOOST_TEST(get<0>(t5) == int());
  BOOST_TEST(get<1>(t5) == float());

  tuple<int, float> t6(12, 5.5f);
  BOOST_TEST(get<0>(t6) == 12);
  BOOST_TEST(get<1>(t6) == 5.5f);

  tuple<long, double> t7(t6);
  BOOST_TEST(get<0>(t7) == 12);
  BOOST_TEST(get<1>(t7) == 5.5f);
}

void
copy_test()
{
  tuple<int, float> t1(4, 12.5f);
  tuple<int, float> t2(5, 2.2f);
  t2 = t1;
  BOOST_TEST(get<0>(t1) == get<0>(t2));
  BOOST_TEST(get<1>(t1) == get<1>(t2));

  tuple<long, double> t3(2, 3.3);
  t3 = t1;
  BOOST_TEST((double)get<0>(t1) == get<0>(t3));
  BOOST_TEST((double)get<1>(t1) == get<1>(t3));
}

void
mutate_test()
{
  tuple<int, float, bool, foo> t1(5, 12.2f, true, foo(4));
  get<0>(t1) = 6;
  get<1>(t1) = 2.2f;
  get<2>(t1) = false;
  get<3>(t1) = foo(5);

  BOOST_TEST(get<0>(t1) == 6);
  BOOST_TEST(get<1>(t1) == 2.2f);
  BOOST_TEST(get<2>(t1) == false);
  BOOST_TEST(get<3>(t1) == foo(5));
}

void
make_tuple_test()
{
  tuple<int, float> t1 = make_tuple(5, 2.25f);
  BOOST_TEST(get<0>(t1) == 5);
  BOOST_TEST(get<1>(t1) == 2.25f);

  tuple<int, double> t2;
  t2 = make_tuple((short int)2, 2.25);
  BOOST_TEST(get<0>(t2) == 2);
  BOOST_TEST(get<1>(t2) == 2.25);
}

void
tie_test()
{
  int a;
  float b;
  foo c(5);

  tie(a, b, c) = make_tuple(2, 5.5f, foo(3));
  BOOST_TEST(a == 2);
  BOOST_TEST(b == 5.5f);
  BOOST_TEST(c == foo(3));

  tie(a, ignore, c) = make_tuple((short int)5, false, foo(5));
  BOOST_TEST(a == 5);
  BOOST_TEST(b == 5.5f);
  BOOST_TEST(c == foo(5));
}

void
equality_test()
{
  tuple<int, float> t1(5, 3.3f);
  tuple<int, float> t2(5, 3.3f);
  BOOST_TEST(t1 == t2);

  tuple<int, float> t3(5, 2.2f);
  tuple<int, float> t4(2, 3.3f);
  BOOST_TEST(t1 != t3);
  BOOST_TEST(t1 != t4);
}

void
ordering_test()
{
  tuple<int, float> t1(4, 3.3f);
  tuple<short, float> t2(5, 3.3f);
  tuple<long, double> t3(5, 4.4);
  BOOST_TEST(t1 < t2);
  BOOST_TEST(t1 <= t2);
  BOOST_TEST(t2 > t1);
  BOOST_TEST(t2 >= t1);
  BOOST_TEST(t2 < t3);
  BOOST_TEST(t2 <= t3);
  BOOST_TEST(t3 > t2);
  BOOST_TEST(t3 >= t2);

}


int
test_main(int, char *[])
{
  construction_test();
  copy_test();
  mutate_test();
  make_tuple_test();
  tie_test();
  equality_test();
  ordering_test();

  return 0;
}
