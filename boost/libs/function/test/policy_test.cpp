#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <cassert>
#include <iostream>
#include <functional>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

struct counting_policy
{
  static int count;

  void precall(function_base*) { count++; }
  void postcall(function_base*) { count+=2; }
};

int counting_policy::count = 0;

int
test_main(int, char*[])
{
  function<int, int, int>::policy<counting_policy>::type f; 

  f = plus<int>();

  BOOST_TEST(5 == f(2,3));
  BOOST_TEST(counting_policy::count==3);

  return 0;
}
