// (C) Copyright Jeremy Siek 2000. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.

#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <iterator>
#include <boost/iterator_adaptors.hpp>

int main(int, char*[])
{
  char characters[] = "abcdefg";
  const int N = sizeof(characters)/sizeof(char) - 1; // -1 since characters has a null char
  char* pointers_to_chars[N];                        // at the end.
  for (int i = 0; i < N; ++i)
    pointers_to_chars[i] = &characters[i];
  
  boost::indirect_iterator_generator<char**, char>::type 
    indirect_first(pointers_to_chars), indirect_last(pointers_to_chars + N);

  std::copy(indirect_first, indirect_last, std::ostream_iterator<char>(std::cout, ","));
  std::cout << std::endl;
  
  return 0;
}
