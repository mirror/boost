// Boost shared_ptr_example2 implementation file  -----------------------------//

#include "shared_ptr_example2.hpp"
#include <iostream>

class example::implementation
{
 public:
  ~implementation() { std::cout << "destroying implementation\n"; }
};

example::example() : _imp( new implementation ) {}

void example::do_something()
  { std::cout << "use_count() is " << _imp.use_count() << "\n"; }
