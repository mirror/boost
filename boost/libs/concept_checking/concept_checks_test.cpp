// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

#include <boost/pending/concept_checks.hpp>
#include <boost/pending/concept_archetypes.hpp>

/*

  This file verifies that the BOOST_FUNCTION_REQUIRES macros of the
  Boost Concept Checking Library do not cause errors when they are not
  suppose to and verifies that the concept archetypes meet the
  requirements of their matching concepts.

*/


int
main()
{
  using namespace boost;
  {
    typedef default_constructible_archetype<> foo;
    BOOST_FUNCTION_REQUIRES(foo, DefaultConstructibleConcept);
  }
  {
    typedef copy_constructible_archetype<> foo;
    BOOST_FUNCTION_REQUIRES(foo, CopyConstructibleConcept);
  }
  {
    typedef assignable_archetype<> foo;
    BOOST_FUNCTION_REQUIRES(foo, AssignableConcept);
  }
  {
    typedef copy_constructible_archetype<> foo;
    typedef convertible_to_archetype<foo> convertible_to_foo;
    BOOST_FUNCTION_REQUIRES2(convertible_to_foo, foo, ConvertibleConcept);
  }
  {
    BOOST_FUNCTION_REQUIRES2(boolean_archetype, bool, ConvertibleConcept);
  }
  {
    typedef unary_function_archetype<int, int> F;
    BOOST_FUNCTION_REQUIRES3(F, int, int, UnaryFunctionConcept);
  }
  {
    typedef binary_function_archetype<int, int, int> F;
    BOOST_FUNCTION_REQUIRES4(F, int, int, int, BinaryFunctionConcept);
  }
  {
    typedef unary_predicate_archetype<int> F;
    BOOST_FUNCTION_REQUIRES2(F, int, UnaryPredicateConcept);
  }
  {
    typedef binary_predicate_archetype<int, int> F;
    BOOST_FUNCTION_REQUIRES3(F, int, int, BinaryPredicateConcept);
    typedef const_binary_predicate_archetype<int, int> const_F;
    BOOST_FUNCTION_REQUIRES3(const_F, int, int, Const_BinaryPredicateConcept);
  }
  {
    typedef trivial_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, TrivialIteratorConcept);
  }
  {
    typedef mutable_trivial_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, Mutable_TrivialIteratorConcept);
  }
  {
    typedef input_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, InputIteratorConcept);
  }
  {
    typedef output_iterator_archetype Iter;
    BOOST_FUNCTION_REQUIRES2(Iter, int, OutputIteratorConcept);
  }
  {
    typedef forward_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, ForwardIteratorConcept);
  }
  {
    typedef bidirectional_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, BidirectionalIteratorConcept);
  }
  {
    typedef random_access_iterator_archetype<null_archetype> Iter;
    BOOST_FUNCTION_REQUIRES(Iter, RandomAccessIteratorConcept);
  }

  return 0;
}
