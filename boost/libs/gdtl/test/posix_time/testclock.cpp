
#include "boost/gdtl/posix_time/posix_time.hpp"
#include <iostream>

int
main() 
{

  using namespace boost::posix_time;
  ptime tl = second_clock::local_time();
  std::cout << to_simple_string(tl) << std::endl;

  ptime tu = second_clock::universal_time();
  std::cout << to_simple_string(tu) << std::endl;

  for (int i=0; i < 3; ++i) {
    ptime t2 = second_clock::local_time();
    std::cout << to_simple_string(t2) << std::endl;
    sleep(1);
  }

//   for (int i=0; i < 10; ++i) {
//     ptime t2 = high_precision_clock::local_time();
//     std::cout << to_simple_string(t2) << std::endl;
//   }


  return 0;

}
