
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/same_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

int main(int argc, char* argv[])
{
   value_test(true, (::boost::is_same<int, int>::value))
   value_test(false, (::boost::is_same<int, const int>::value))
   value_test(false, (::boost::is_same<int, int&>::value))
   value_test(false, (::boost::is_same<const int, int&>::value))
   value_test(false, (::boost::is_same<int, const int&>::value))
   value_test(false, (::boost::is_same<int*, const int*>::value))
   value_test(false, (::boost::is_same<int*, int*const>::value))
   value_test(false, (::boost::is_same<int, int[2]>::value))
   value_test(false, (::boost::is_same<int*, int[2]>::value))
   value_test(false, (::boost::is_same<int[4], int[2]>::value))

   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
unsigned int expected_failures = 0;

