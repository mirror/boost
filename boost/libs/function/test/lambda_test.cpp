#include <iostream>
#include <cstdlib>

#include <boost/test/test_tools.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;
using namespace boost::lambda;

static unsigned
func_impl(int arg1, bool arg2, double arg3)
{
  return abs (static_cast<int>((arg2 ? arg1 : 2 * arg1) * arg3));
}

int test_main(int, char*[])
{
  function <unsigned(bool, double)> f1 = bind(func_impl, 15, _1, _2);
  function <unsigned(double)>       f2 = bind(f1, false, _1);
  function <unsigned()>             f3 = bind(f2, 4.0);

  unsigned result = f3();

  return 0;
}

