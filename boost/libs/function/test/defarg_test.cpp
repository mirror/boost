#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/function.hpp>
#include <functional>
#include <cassert>
#include <string>

using namespace std;
using namespace boost;

static int sub_ints(int x = 0, int y = 0, int z = 0) { return x-y-z; }

static void
test_two_args()
{
  function<int, int, int> sub(&sub_ints);
  BOOST_TEST(sub(10, 2) == 8);
}

int
test_main(int, char* [])
{
  test_two_args();
  return 0;
}
