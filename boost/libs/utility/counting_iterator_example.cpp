// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.


#include <boost/config.hpp>
#include <iostream>
#include <boost/counting_iterator.hpp>

int main(int, char*[])
{
  // Example of using counting_iterator_generator
  std::cout << "counting from 0 to 4:" << std::endl;
  boost::counting_iterator_generator<int>::type first(0), last(4);
  std::copy(first, last, std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;

  // Example of using make_counting_iterator()
  std::cout << "counting from -5 to 5:" << std::endl;
  std::copy(boost::make_counting_iterator(-5),
	    boost::make_counting_iterator(5),
	    std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;


  return 0;
}
