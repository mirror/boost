//  (C) Copyright Jeremy Siek 2001. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

#include <boost/property_map.hpp>

// This file checks the property map concepts against the property map
// archetypes to make sure they are consistent and that they compile.

int
main()
{
  using namespace boost;
  {
    typedef null_archetype<> Key;
    typedef assignable_archetype<copy_constructible_archetype<> > Value;
    typedef readable_property_map_archetype<Key, Value> PMap;
    function_requires<ReadablePropertyMapConcept<PMap, Key> >();
  }
  {
    typedef null_archetype<> Key;
    typedef assignable_archetype<copy_constructible_archetype<> > Value;
    typedef writable_property_map_archetype<Key, Value> PMap;
    function_requires<WritablePropertyMapConcept<PMap, Key> >();
  }
  {
    typedef null_archetype<> Key;
    typedef assignable_archetype<copy_constructible_archetype<> > Value;
    typedef read_write_property_map_archetype<Key, Value> PMap;
    function_requires<ReadWritePropertyMapConcept<PMap, Key> >();
  }
  {
    typedef null_archetype<> Key;
    typedef assignable_archetype<copy_constructible_archetype<> > Value;
    typedef lvalue_property_map_archetype<Key, Value> PMap;
    function_requires<LvaluePropertyMapConcept<PMap, Key> >();
  }
  {
    typedef null_archetype<> Key;
    typedef assignable_archetype<copy_constructible_archetype<> > Value;
    typedef mutable_lvalue_property_map_archetype<Key, Value> PMap;
    function_requires<Mutable_LvaluePropertyMapConcept<PMap, Key> >();
  }
  return 0;
}
