#include <list>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <iostream>

#include <boost/minmax.hpp>

int main()
{
  using namespace std;
  list<int> L;
  generate_n(front_inserter(L), 1000, rand);

  typedef list<int>::const_iterator iterator;
  pair< iterator, iterator > result = boost::minmax_element(L.begin(), L.end());

  cout << "The smallest element is " << *(result.first) << endl;
  cout << "The largest element is  " << *(result.second) << endl;

  assert( result.first  == std::min_element(L.begin(), L.end()) );
  assert( result.second == std::max_element(L.begin(), L.end()) );
}
