#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/function.hpp>

using namespace std;
using namespace boost;

int
test_main(int, char*[])
{
  function<int> f1;
  function<int> f2;

  if (f1 == f2) {
  }

  BOOST_CRITICAL_ERROR("This should not have compiled.");

  return 0;
}
