// (C) Copyright Ronald Garcia 2003. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

#include "boost/shared_container_iterator.hpp"
#include "boost/shared_ptr.hpp"
#include <vector>
#include <cassert>

struct resource {
  static int count;
  resource() { ++count; }
  resource(resource const&) { ++count; }
  ~resource() { --count; }
};
int resource::count = 0;

typedef std::vector<resource> resources_t;

typedef boost::shared_container_iterator< resources_t > iterator;


void set_range(iterator& i, iterator& end)  {

  boost::shared_ptr< resources_t > objs(new resources_t());

  for (int j = 0; j != 6; ++j)
    objs->push_back(resource());
  
  i = iterator(objs->begin(),objs);
  end = iterator(objs->end(),objs);
  assert(resource::count == 6);
}


int main() {

  assert(resource::count == 0);
  
  {
    iterator i;
    {
      iterator end;
      set_range(i,end);
      assert(resource::count == 6);
    }
    assert(resource::count == 6);
  }
  assert(resource::count == 0);
  
  return 0;
}
