// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_checks.hpp>

/*

  This file verifies that the boost::class_requires class of the Boost
  Concept Checking Library do not cause errors when it is not suppose
  to.

*/

struct foo { bool operator()(int) { return true; } };
struct bar { bool operator()(int, char) { return true; } };

using namespace boost;

class class_requires_test
{
  typedef class_requires< EqualityComparableConcept<int> >::check req1;
  typedef class_requires<EqualityComparableConcept<int> >::check req2;
  typedef class_requires<Comparable2Concept<int*, const int*> >::check req3;
  typedef class_requires<UnaryFunctionConcept<foo, bool, int> >::check req4;
  typedef class_requires<BinaryFunctionConcept<bar, bool, int, char> >::check
    req5;
};

int
main()
{
  class_requires_test x;
  ignore_unused_variable_warning(x);
  return 0;
}
