#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

static int bad_fn(float f) { return static_cast<int>(f); }

int
test_main(int, char*[])
{
  function<int> f1;
  f1 = bad_fn;

  BOOST_CRITICAL_ERROR("This should not have compiled.");

  return 0;
}
