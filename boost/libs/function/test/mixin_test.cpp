#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <cassert>
#include <functional>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

struct id_mixin
{
  int id;
};

int
test_main(int, char*[])
{
  function<int, int, int>::mixin<id_mixin>::type f;
  f = plus<int>();
  f.id = 7;
  f.clear();
  BOOST_TEST(f.id == 7);

  return 0;
}
