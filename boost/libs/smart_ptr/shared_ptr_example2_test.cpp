// Boost shared_ptr_example2_test main program  ------------------------------//

#include "shared_ptr_example2.hpp"

int main()
{
  example a;
  a.do_something();
  example b(a);
  b.do_something();
  example c;
  c = a;
  c.do_something();
  return 0;
}