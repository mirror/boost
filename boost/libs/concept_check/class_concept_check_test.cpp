// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_check.hpp>

/*

  This file verifies that the BOOST_CLASS_REQUIRES macro of the Boost
  Concept Checking Library does not cause errors when it is not suppose
  to.

*/

struct foo { bool operator()(int) { return true; } };
struct bar { bool operator()(int, char) { return true; } };

using namespace boost;

class class_requires_test
{
  BOOST_CLASS_REQUIRES(int, EqualityComparableConcept);
  typedef int* int_ptr; typedef const int* const_int_ptr;
  BOOST_CLASS_REQUIRES2(int_ptr, const_int_ptr, Comparable2Concept);
  BOOST_CLASS_REQUIRES3(foo, bool, int, UnaryFunctionConcept);
  BOOST_CLASS_REQUIRES4(bar, bool, int, char, BinaryFunctionConcept);
};

int
main()
{
  class_requires_test x;
  ignore_unused_variable_warning(x);
  return 0;
}
