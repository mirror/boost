//  boost integer.hpp header file  -------------------------------------------//

//  Copyright Beman Dawes and Daryle Walker 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

//  Revision History
//   13 Jul 08  Redid implmentation. (Daryle Walker)
//   22 Sep 01  Added value-based integer templates. (Daryle Walker)
//   01 Apr 01  Modified to use new <boost/limits.hpp> header. (John Maddock)
//   30 Jul 00  Add typename syntax fix (Jens Maurer)
//   28 Aug 99  Initial version

#ifndef BOOST_INTEGER_HPP
#define BOOST_INTEGER_HPP

#include <boost/integer_fwd.hpp>  // self include

#include <boost/config.hpp>          // for BOOST_STATIC_CONSTANT
#include <boost/integer_traits.hpp>  // for boost::integer_traits
#include <boost/limits.hpp>          // for std::numeric_limits

namespace boost
{

  //  integer template mapping a type to its processor-optimized analog  -----//

  //  fast integers from least integers
  //  int_fast_t<> works correctly for unsigned too, in spite of the name.
  template< typename LeastInt >
  struct int_fast_t { typedef LeastInt fast; }; // imps may specialize

namespace detail
{

  //  Helper templates  ------------------------------------------------------//

  //  convert integer category to type ; default is empty
  template< int Rank, typename Signedness > struct  int_least_helper {};

  //  specializatons: 1=(unsigned) long, 2=unsigned/int, 3=(unsigned) short,
  //     4=(un)signed char
  //  no specializations for 0: requests for a type > (unsigned) long are in
  //     error
  template<> struct int_least_helper<1, signed> { typedef long least; };
  template<> struct int_least_helper<1, unsigned>
   { typedef unsigned long least; };
  template<> struct int_least_helper<2, signed> { typedef int least; };
  template<> struct int_least_helper<2, unsigned>
   { typedef unsigned int least; };
  template<> struct int_least_helper<3, signed> { typedef short least; };
  template<> struct int_least_helper<3, unsigned>
   { typedef unsigned short least; };
  template<> struct int_least_helper<4, signed> { typedef signed char least; };
  template<> struct int_least_helper<4, unsigned>
   { typedef unsigned char least; };

  //  category bounds
  enum
  {
      lowest_integral_rank  = 1,
      highest_integral_rank = 4
  };

  //  map a bit count to a category
  template < int BitsIncludingSign >
  struct int_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, rank =
       (BitsIncludingSign - 1 <= std::numeric_limits< long >::digits) +
       (BitsIncludingSign - 1 <= std::numeric_limits< int >::digits) +
       (BitsIncludingSign - 1 <= std::numeric_limits< short >::digits) +
       (BitsIncludingSign - 1 <= std::numeric_limits< signed char >::digits) );
  };

  template < int Bits >
  struct uint_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, rank =
       (Bits <= std::numeric_limits< unsigned long >::digits) +
       (Bits <= std::numeric_limits< unsigned int >::digits) +
       (Bits <= std::numeric_limits< unsigned short >::digits) +
       (Bits <= std::numeric_limits< unsigned char >::digits) );
  };

  //  map an extreme value to a category
  template < long MaxValue >
  struct int_max_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, rank =
       (MaxValue <= integer_traits< long >::const_max) +
       (MaxValue <= integer_traits< int >::const_max) +
       (MaxValue <= integer_traits< short >::const_max) +
       (MaxValue <= integer_traits< signed char >::const_max) );
  };

  template < long MinValue >
  struct int_min_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, rank =
       (MinValue >= integer_traits< long >::const_min) +
       (MinValue >= integer_traits< int >::const_min) +
       (MinValue >= integer_traits< short >::const_min) +
       (MinValue >= integer_traits< signed char >::const_min) );
  };

  template < unsigned long Value >
  struct uint_max_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, rank =
       (Value <= integer_traits< unsigned long >::const_max) +
       (Value <= integer_traits< unsigned int >::const_max) +
       (Value <= integer_traits< unsigned short >::const_max) +
       (Value <= integer_traits< unsigned char >::const_max) );
  };

} // namespace detail

  //  integer templates specifying number of bits  ---------------------------//

  //  signed
  template< int Bits >   // bits (including sign) required
  struct int_t 
  {
      typedef typename detail::int_least_helper
        <
          detail::int_rank_helper<Bits>::rank,
        signed>::least  least;
      typedef typename int_fast_t<least>::fast  fast;
  };

  //  unsigned
  template< int Bits >   // bits required
  struct uint_t 
  {
      typedef typename detail::int_least_helper
        < 
          detail::uint_rank_helper<Bits>::rank,
        unsigned>::least  least;
      typedef typename int_fast_t<least>::fast  fast;
      // int_fast_t<> works correctly for unsigned too, in spite of the name.
  };

  //  integer templates specifying extreme value  ----------------------------//

  //  signed
  template< long MaxValue >   // maximum value to require support
  struct int_max_value_t 
  {
      typedef typename detail::int_least_helper
        <
          detail::int_max_rank_helper<MaxValue>::rank,
        signed>::least  least;
      typedef typename int_fast_t<least>::fast  fast;
  };

  template< long MinValue >   // minimum value to require support
  struct int_min_value_t 
  {
      typedef typename detail::int_least_helper
        <
          detail::int_min_rank_helper<MinValue>::rank,
        signed>::least  least;
      typedef typename int_fast_t<least>::fast  fast;
  };

  //  unsigned
  template< unsigned long Value >   // maximum value to require support
  struct uint_value_t 
  {
      typedef typename detail::int_least_helper
        < 
          detail::uint_max_rank_helper<Value>::rank,
        unsigned>::least  least;
      typedef typename int_fast_t<least>::fast  fast;
  };


} // namespace boost

#endif  // BOOST_INTEGER_HPP
