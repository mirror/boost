

#include <boost/function.hpp>
#include <iostream>


struct stateful_type { int operator()(int) const { return 0; } };

int main()
{
  
  stateful_type a_function_object;
  boost::function1<int, int> f;
  f = boost::ref(a_function_object);

  boost::function1<int, int> f2(f);

}
