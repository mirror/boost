// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

//
// This file checks to see if various standard container
// implementations live up to requirements specified in the C++
// standard. As many implementations do not live to the requirements,
// it is not uncommon for this file to fail to compile. The
// BOOST_HIDE_EXPECTED_ERRORS macro is provided here if you want to
// see as much of this file compile as possible.
//

#include <boost/pending/concept_checks.hpp>

#include <iterator>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <deque>
#ifndef BOOST_NO_SLIST
#include <slist>
#endif

//#define BOOST_HIDE_EXPECTED_ERRORS

int
main()
{
#if defined(_ITERATOR_) && defined(BOOST_HIDE_EXPECTED_ERRORS)
  // VC++ STL implementation is not standard conformant and
  // fails to pass these concept checks
#else
  typedef std::vector<int> Vector;
  typedef std::deque<int> Deque;
  typedef std::list<int> List;

  // VC++ missing pointer and const_pointer typedefs
  BOOST_FUNCTION_REQUIRES(Vector, Mutable_RandomAccessContainerConcept);
  BOOST_FUNCTION_REQUIRES(Vector, BackInsertionSequenceConcept);

#if !(defined(__GNUC__) && defined(BOOST_HIDE_EXPECTED_ERRORS))
#if !(defined(__sgi) && defined(BOOST_HIDE_EXPECTED_ERRORS))
  // old deque iterator missing n + iter operation
  BOOST_FUNCTION_REQUIRES(Deque, Mutable_RandomAccessContainerConcept);
#endif
  // warnings about signed and unsigned in old deque version
  BOOST_FUNCTION_REQUIRES(Deque, FrontInsertionSequenceConcept);
  BOOST_FUNCTION_REQUIRES(Deque, BackInsertionSequenceConcept);
#endif

  // VC++ missing pointer and const_pointer typedefs
  BOOST_FUNCTION_REQUIRES(List, Mutable_ReversibleContainerConcept);
  BOOST_FUNCTION_REQUIRES(List, FrontInsertionSequenceConcept);
  BOOST_FUNCTION_REQUIRES(List, BackInsertionSequenceConcept);

#ifndef BOOST_NO_SLIST
  typedef std::slist<int> SList;
  BOOST_FUNCTION_REQUIRES(SList, FrontInsertionSequenceConcept);
#endif

  typedef std::set<int> Set;
  typedef std::multiset<int> MultiSet;
  typedef std::map<int,int> Map;
  typedef std::multimap<int,int> MultiMap;

  BOOST_FUNCTION_REQUIRES(Set, SortedAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(Set, SimpleAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(Set, UniqueAssociativeContainerConcept);

  BOOST_FUNCTION_REQUIRES(MultiSet, SortedAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(MultiSet, SimpleAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(MultiSet, MultipleAssociativeContainerConcept);

  BOOST_FUNCTION_REQUIRES(Map, SortedAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(Map, UniqueAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(Map, PairAssociativeContainerConcept);

  BOOST_FUNCTION_REQUIRES(MultiMap, SortedAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(MultiMap, MultipleAssociativeContainerConcept);
  BOOST_FUNCTION_REQUIRES(MultiMap, PairAssociativeContainerConcept);
#endif

  return 0;
}
