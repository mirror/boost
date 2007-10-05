// Copyright 2007 Fernando Luis Cacciola Carballal.  Use, modification, and distribution
// are subject to the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/utility for documentation.

// Boost test program for noost::none_t and boost::none

// Test strategy contributed by Richard Smith

#include <boost/optional/optional.hpp> // Test none.hpp is included with <optional.hpp>

// Left undefined to cause a linker error if this overload is incorrectly selected.
void verify_no_implicit_conversion_to_int ( int i ) ;

void verify_no_implicit_conversion_to_int ( boost::optional<int> const& ) {}

int main() 
{
  verify_no_implicit_conversion_to_int( boost::none );
}
