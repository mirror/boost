
//  (C) Copyright John Maddock 2000. Permission to copy, use, modify, sell and   
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

#include <boost/type_traits/alignment_traits.hpp>
#include <boost/utility.hpp>

#ifdef __BORLANDC__
#pragma hrdstop
#endif
#include "boost/type_traits/type_traits_test.hpp"

NESTED_DECL(alignment_of)

int main(int argc, char* argv[])
{
   NESTED_TEST(alignment_of, int)
   NESTED_TEST(alignment_of, int_constructible)

   align_test(int);
   align_test(char);
   align_test(double);
   align_test(int[4]);
   align_test(int(*)(int));
#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
   align_test(char&);
   align_test(char (&)(int));
   align_test(char(&)[4]);
#endif
   align_test(int*);
   //align_test(const int);
   align_test(VB);
   align_test(VD);
   value_test(0, ::boost::alignment_of<void>::value);
   
   return check_result(argc, argv);
}

//
// define the number of failures expected for given compilers:
unsigned int expected_failures = 0;

