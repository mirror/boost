// Example of using the filter iterator adaptor from
// boost/iterator_adaptors.hpp.

//  (C) Copyright Jeremy Siek 1999. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.


#include <boost/config.hpp>
#include <algorithm>
#include <iostream>
#include <boost/iterator_adaptors.hpp>

struct is_positive_number {
  bool operator()(int x) { return 0 < x; }
};

int main()
{
  int numbers[] = { 0, -1, 4, -3, 5, 8, -2 };
  const int N = sizeof(numbers)/sizeof(int);

  std::copy(boost::make_filter_iterator<is_positive_number>(numbers, numbers + N),
	    boost::make_filter_iterator<is_positive_number>(numbers + N, numbers + N),
	    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
  return 0;
}
