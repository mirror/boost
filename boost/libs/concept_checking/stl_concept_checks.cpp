// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
// sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.

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

int
main()
{
#if defined(_ITERATOR_)
  // VC++ STL implementation is not standard conformant and
  // fails to pass these concept checks
#else
  typedef std::vector<int> Vector;
  typedef std::deque<int> Deque;
  typedef std::list<int> List;

  // VC++ missing pointer and const_pointer typedefs
  REQUIRE(Vector, Mutable_RandomAccessContainer);
  REQUIRE(Vector, BackInsertionSequence);

#if !defined(__GNUC__)
#if !defined __sgi
  // old deque iterator missing n + iter operation
  REQUIRE(Deque, Mutable_RandomAccessContainer);
#endif
  // warnings about signed and unsigned in old deque version
  REQUIRE(Deque, FrontInsertionSequence);
  REQUIRE(Deque, BackInsertionSequence);
#endif

  // VC++ missing pointer and const_pointer typedefs
  REQUIRE(List, Mutable_ReversibleContainer);
  REQUIRE(List, FrontInsertionSequence);
  REQUIRE(List, BackInsertionSequence);

#ifndef BOOST_NO_SLIST
  typedef std::slist<int> SList;
  REQUIRE(SList, FrontInsertionSequence);
#endif

  typedef std::set<int> Set;
  typedef std::multiset<int> MultiSet;
  typedef std::map<int,int> Map;
  typedef std::multimap<int,int> MultiMap;

  REQUIRE(Set, SortedAssociativeContainer);
  REQUIRE(Set, SimpleAssociativeContainer);
  REQUIRE(Set, UniqueAssociativeContainer);

  REQUIRE(MultiSet, SortedAssociativeContainer);
  REQUIRE(MultiSet, SimpleAssociativeContainer);
  REQUIRE(MultiSet, MultipleAssociativeContainer);

  REQUIRE(Map, SortedAssociativeContainer);
  REQUIRE(Map, UniqueAssociativeContainer);
  REQUIRE(Map, PairAssociativeContainer);

  REQUIRE(MultiMap, SortedAssociativeContainer);
  REQUIRE(MultiMap, MultipleAssociativeContainer);
  REQUIRE(MultiMap, PairAssociativeContainer);
#endif

  return 0;
}
