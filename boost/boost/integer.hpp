//  boost integer.hpp header file  -------------------------------------------//

//  (C) Copyright Beman Dawes 1999. Permission to copy, use, modify, sell
//  and distribute this software is granted provided this copyright
//  notice appears in all copies. This software is provided "as is" without
//  express or implied warranty, and with no claim as to its suitability for
//  any purpose.

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//   30 Jul 00  Add typename syntax fix (Jens Maurer) 
//   28 Aug 99  Initial version

#ifndef BOOST_INTEGER_HPP
#define BOOST_INTEGER_HPP

#include <limits>

namespace boost
{

  //  Helper templates  ------------------------------------------------------//

  //  fast integers from least integers
  template< typename LeastInt >
  struct int_fast_t { typedef LeastInt fast; }; // imps may specialize

  //  convert category to type 
  template< int Category > struct int_least_helper {}; // default is empty

  //  specializatons: 1=long, 2=int, 3=short, 4=signed char,
  //     6=unsigned long, 7=unsigned int, 8=unsigned short, 9=unsigned long
  template<> struct int_least_helper<1> { typedef long least; };
  template<> struct int_least_helper<2> { typedef int least; };
  template<> struct int_least_helper<3> { typedef short least; };
  template<> struct int_least_helper<4> { typedef signed char least; };
  template<> struct int_least_helper<6> { typedef unsigned long least; };
  template<> struct int_least_helper<7> { typedef unsigned int least; };
  template<> struct int_least_helper<8> { typedef unsigned short least; };
  template<> struct int_least_helper<9> { typedef unsigned char least; };

  //  integer templates specifying number of bits  ---------------------------//

  //  signed
  template< int Bits >   // bits (including sign) required
  struct int_t 
  {
      typedef typename int_least_helper
        <
          (Bits-1 <= std::numeric_limits<long>::digits) +
          (Bits-1 <= std::numeric_limits<int>::digits) +
          (Bits-1 <= std::numeric_limits<short>::digits) +
          (Bits-1 <= std::numeric_limits<signed char>::digits)
        >::least  least;
      typedef int_fast_t<least>::fast  fast;
  };

  //  unsigned
  template< int Bits >   // bits required
  struct uint_t 
  {
      typedef typename int_least_helper
        < 
          5 +
          (Bits <= std::numeric_limits<unsigned long>::digits) +
          (Bits <= std::numeric_limits<unsigned int>::digits) +
          (Bits <= std::numeric_limits<unsigned short>::digits) +
          (Bits <= std::numeric_limits<unsigned char>::digits)
        >::least  least;
      typedef int_fast_t<least>::fast  fast;
  };

//  The same dispatching technique can be used to select types based on
//  values.  That will be added once boost::integer_traits is available.


} // namespace boost

#endif  // BOOST_INTEGER_HPP
