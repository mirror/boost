//
// Copyright Thomas Witt 2003. Permission to copy, use,
// modify, sell and distribute this software is granted provided this
// copyright notice appears in all copies. This software is provided
// "as is" without express or implied warranty, and with no claim as
// to its suitability for any purpose.
//
#include <boost/iterator/iterator_archetypes.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <boost/concept_check.hpp>

int main()
{
  {
    typedef boost::iterator_archetype<int, 
      boost::writable_lvalue_iterator_tag,
      boost::random_access_traversal_tag> iter;

    boost::function_requires< boost_concepts::WritableLvalueIteratorConcept<iter> >();
    boost::function_requires< boost_concepts::RandomAccessTraversalConcept<iter> >();
  }
  return 0; // keep msvc happy
}

