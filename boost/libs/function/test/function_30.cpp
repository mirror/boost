// Make sure we don't try to redefine function2
#include <boost/function/function2.hpp>

// Define all Boost.Function class templates up to 30 arguments
#define BOOST_FUNCTION_MAX_ARGS 30
#include <boost/function.hpp>

int main()
{
  boost::function0<float> f0;

  boost::function30<float, int, int, int, int, int, int, int, int, int, int,
                    int, int, int, int, int, int, int, int, int, int,
                    int, int, int, int, int, int, int, int, int, int> f30;
  return 0;
}
