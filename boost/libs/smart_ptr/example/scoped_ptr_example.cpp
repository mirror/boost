// Boost scoped_ptr_example implementation file  -----------------------------//

#include "scoped_ptr_example.hpp"
#include <iostream>

class example::implementation
{
 public:
  ~implementation() { std::cout << "destroying implementation\n"; }
};

example::example() : _imp( new implementation ) {}

void example::do_something() { std::cout << "did something\n"; }

example::~example() {}
