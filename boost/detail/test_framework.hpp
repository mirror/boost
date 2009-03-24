//  test_framework.hpp  ----------------------------------------------------------------//

//  Copyright Beman Dawes 2009

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  A very simple test framework that avoids dependencies on Boost.Test

#include <iostream>

namespace boost
{
  namespace test_framework
  {
    int error_count = 0;

    void check( const char * predicate, const char * file, int line )
    {
      ++error_count;

      //  format chosen to parse with VC++ IDE output
      std::cout << file << "(" << line << ") : error: "
                << predicate << " is false\n" << std::endl;
    }

    int errors()
    {
      std::cout << "     ***** " << error_count << " error(s) detected *****\n";
      return error_count;
    }
  }  // namespace test_framework
}  // namespace boost

#define BOOST_CHECK(predicate) \
  (predicate) ? static_cast<void>(0) : \
  boost::test_framework::check( #predicate, __FILE__, __LINE__ )
