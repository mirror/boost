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
    function_requires< DefaultConstructibleConcept<foo> >();
  }
  {
    typedef copy_constructible_archetype<> foo;
    function_requires< CopyConstructibleConcept<foo> >();
  }
  {
    typedef assignable_archetype<> foo;
    function_requires< AssignableConcept<foo> >();
  }
  {
    typedef copy_constructible_archetype<> foo;
    typedef convertible_to_archetype<foo> convertible_to_foo;
    function_requires< ConvertibleConcept<convertible_to_foo, foo> >();
  }
  {
    function_requires< ConvertibleConcept<boolean_archetype, bool> >();
  }
  {
    typedef unary_function_archetype<int, int> F;
    function_requires< UnaryFunctionConcept<F, int, int> >();
  }
  {
    typedef binary_function_archetype<int, int, int> F;
    function_requires< BinaryFunctionConcept<F, int, int, int> >();
  }
  {
    typedef unary_predicate_archetype<int> F;
    function_requires< UnaryPredicateConcept<F, int> >();
  }
  {
    typedef binary_predicate_archetype<int, int> F;
    function_requires< BinaryPredicateConcept<F, int, int> >();
    typedef const_binary_predicate_archetype<int, int> const_F;
    function_requires< Const_BinaryPredicateConcept<const_F, int, int> >();
  }
  {
    typedef trivial_iterator_archetype<null_archetype> Iter;
    function_requires< TrivialIteratorConcept<Iter> >();
  }
  {
    typedef mutable_trivial_iterator_archetype<null_archetype> Iter;
    function_requires< Mutable_TrivialIteratorConcept<Iter> >();
  }
  {
    typedef input_iterator_archetype<null_archetype> Iter;
    function_requires< InputIteratorConcept<Iter> >();
  }
  {
    typedef output_iterator_archetype Iter;
    function_requires< OutputIteratorConcept<Iter, int> >();
  }
  {
    typedef forward_iterator_archetype<null_archetype> Iter;
    function_requires< ForwardIteratorConcept<Iter> >();
  }
  {
    typedef bidirectional_iterator_archetype<null_archetype> Iter;
    function_requires< BidirectionalIteratorConcept<Iter> >();
  }
  {
    typedef random_access_iterator_archetype<null_archetype> Iter;
    function_requires< RandomAccessIteratorConcept<Iter> >();
  }

  return 0;
}
