// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_checks.hpp>

/*

  This file verifies that the BOOST_CLASS_REQUIRES3 macro
  of the Boost Concept Checking Library catches errors
  when it is suppose to.

*/

struct foo { };

class class_requires_test
{
  BOOST_CLASS_REQUIRES3(foo, foo, foo, UnaryFunctionConcept);
};

int
main()
{
  class_requires_test x;
  return 0;
}
