//  (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify,
//  sell and distribute this software is granted provided this
//  copyright notice appears in all copies. This software is provided
//  "as is" without express or implied warranty, and with no claim as
//  to its suitability for any purpose.

/*
  An example of using array traits with multi-dimensional arrays.
  Contributed by Jeremy Siek

  Sample output:
  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 
  -----------
  0 1 2 3 
  -----------
  4 5 6 7 
  -----------
  0 1 2 3 
  4 5 6 7 
  8 9 10 11 
  12 13 14 15 
  16 17 18 19 
  20 21 22 23 

 */

#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/array_traits.hpp>

int
main()
{
  const int M = 2, N = 3, K = 4;
  typedef int c_type[M][N][K];
  c_type c;
  int x = 0;
  for (int i = 0; i < M; ++i)
    for (int j = 0; j < N; ++j)
      for (int k = 0; k < K; ++k)
        c[i][j][k] = x++;

  using namespace boost;

  std::copy(&c[0][0][0], &c[0][0][0] + size(c) * size(c[0]) * size(c[0][0]), 
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "-----------" << std::endl;
  std::copy(begin(c[0][0]), end(c[0][0]), 
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "-----------" << std::endl;
  std::copy(begin(c[0][1]), end(c[0][1]), 
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  std::cout << "-----------" << std::endl;

  typedef array_traits<c_type>::iterator iter_type1;
  typedef array_traits<c_type>::value_type value_type1;
  typedef array_traits<value_type1>::iterator iter_type2;
  
  for (iter_type1 iter1 = begin(c); iter1 != end(c); ++iter1)
    for (iter_type2 iter2 = begin(*iter1); iter2 != end(*iter1); ++iter2) {
      std::copy(begin(*iter2), end(*iter2), 
		std::ostream_iterator<int>(std::cout, " "));
      std::cout << std::endl;
    }

  return 0;
}
