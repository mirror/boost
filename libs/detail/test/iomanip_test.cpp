/*<-============================================================================
    Copyright (c) 2010      Bryce Lelbach

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
============================================================================->*/

#include <iostream>
#include <sstream>

#include <boost/detail/iomanip.hpp>
#include <boost/detail/lightweight_test.hpp>

int main (void) {
  using namespace boost::detail;

  std::ostringstream oss(std::ostringstream::out);

  //[setbase_test
  oss << setbase(8) << 8;
  BOOST_TEST(oss.str() == "10");
  
  oss.str("");
  oss << setbase(10) << 10;
  BOOST_TEST(oss.str() == "10");

  oss.str("");
  oss << setbase(16) << 16;
  BOOST_TEST(oss.str() == "10");
  //]

  //[setiosflags_test
  oss.str("");
  oss << setiosflags(std::ios_base::showbase | std::ios_base::hex) << 16;
  BOOST_TEST(oss.str() == "0x10");
  //]
  
  //[resetiosflags_test
  oss.str("");
  oss << resetiosflags(std::ios_base::showbase | std::ios_base::hex) << 16;
  BOOST_TEST(oss.str() == "16");
  //]

  //[setprecision_test
  oss.str("");
  oss << setprecision(4) << 3.14159;
  BOOST_TEST(oss.str() == "3.142");
  //]

  //[setfill_and_setw_test
  oss.str("");
  oss << setfill('*') << setw(5) << 9;
  BOOST_TEST(oss.str() == "****9");
  //]

  return boost::report_errors();
}

