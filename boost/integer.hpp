//  boost integer.hpp header file  -------------------------------------------//

//  Copyright Beman Dawes and Daryle Walker 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

//  Revision History
//   16 Jul 08  Added MPL-compatible variants of the minimum-size and value-
//              based integer templates. (Daryle Walker)
//   15 Jul 08  Added exact-integer templates; added MPL-compatible variant of
//              processor-optimized integer template. (Daryle Walker)
//   14 Jul 08  Added extended-integer support. (Daryle Walker)
//   13 Jul 08  Redid implmentation. (Daryle Walker)
//   22 Sep 01  Added value-based integer templates. (Daryle Walker)
//   01 Apr 01  Modified to use new <boost/limits.hpp> header. (John Maddock)
//   30 Jul 00  Add typename syntax fix (Jens Maurer)
//   28 Aug 99  Initial version

#ifndef BOOST_INTEGER_HPP
#define BOOST_INTEGER_HPP

#include <boost/integer_fwd.hpp>  // self include

#include <boost/config.hpp>             // for BOOST_STATIC_CONSTANT, etc.
#include <boost/cstdint.hpp>            // for boost::uintmax_t, intmax_t
#include <boost/integer_traits.hpp>     // for boost::integer_traits
#include <boost/limits.hpp>             // for std::numeric_limits
#include <boost/utility/enable_if.hpp>  // for boost::enable_if_c

#include <boost/detail/extended_integer.hpp>  // for BOOST_HAS_XINT, etc.

#include <climits>  // for UCHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX, etc.

namespace boost
{

  //  integer template mapping a type to its processor-optimized analog  -----//

  //  Some types can be handled better by the processor than others.  This
  //  template metafunction should map various built-in integral types to
  //  the processor's perferred type for the given type's value range
  template < typename BaseInt >
  struct fast_integral
  {
      typedef BaseInt  type;
  };

  // Platform-specific specializations should go here.

  //  fast integers from least integers
  //  int_fast_t<> works correctly for unsigned too, in spite of the name.
  template< typename LeastInt >
  struct int_fast_t { typedef typename fast_integral<LeastInt>::type fast; };

namespace detail
{

  //  Helper templates  ------------------------------------------------------//

  //  convert integer category to type ; default is empty
  template< int Rank, typename Signedness > struct  int_least_helper {};

  //  specializatons: 1=(unsigned) __int64/long long, 2=(unsigned) long,
  //     3=unsigned/int, 4=(unsigned) short, 5=(un)signed char
  //  no specializations for 0: requests for a type > (unsigned) (long) long are
  //     in error
#if BOOST_HAS_XINT
  template<> struct int_least_helper<1,   signed>  { typedef  xint_t least; };
  template<> struct int_least_helper<1, unsigned>  { typedef uxint_t least; };
#endif
  template<> struct int_least_helper<2, signed> { typedef long least; };
  template<> struct int_least_helper<2, unsigned>
   { typedef unsigned long least; };
  template<> struct int_least_helper<3, signed> { typedef int least; };
  template<> struct int_least_helper<3, unsigned>
   { typedef unsigned int least; };
  template<> struct int_least_helper<4, signed> { typedef short least; };
  template<> struct int_least_helper<4, unsigned>
   { typedef unsigned short least; };
  template<> struct int_least_helper<5, signed> { typedef signed char least; };
  template<> struct int_least_helper<5, unsigned>
   { typedef unsigned char least; };

  //  category bounds
  enum
  {
#if BOOST_HAS_XINT
      lowest_integral_rank  = 1,
#else
      lowest_integral_rank  = 2,
#endif
      highest_integral_rank = 5
  };

  //  map a bit count to a category
  template < int BitsIncludingSign >
  struct int_rank_helper
  {
      BOOST_STATIC_CONSTANT( int, mantissa = BitsIncludingSign - 1 );
#if BOOST_HAS_XINT
      BOOST_STATIC_CONSTANT( int, extended_ = (mantissa <= std::numeric_limits<
       xint_t >::digits) );
#else
      BOOST_STATIC_CONSTANT( int, extended_ = 1 );
#endif
      BOOST_STATIC_CONSTANT( int, rank = (BitsIncludingSign > 0) * (extended_ +
       (mantissa <= std::numeric_limits< long >::digits) +
       (mantissa <= std::numeric_limits< int >::digits) +
       (mantissa <= std::numeric_limits< short >::digits) +
       (mantissa <= std::numeric_limits< signed char >::digits)) );
  };

  template < int Bits >
  struct uint_rank_helper
  {
#if BOOST_HAS_XINT
      BOOST_STATIC_CONSTANT( int, extended_ = (Bits <= std::numeric_limits<
       uxint_t >::digits) );
#else
      BOOST_STATIC_CONSTANT( int, extended_ = 1 );
#endif
      BOOST_STATIC_CONSTANT( int, rank = (Bits >= 0) * (extended_ +
       (Bits <= std::numeric_limits< unsigned long >::digits) +
       (Bits <= std::numeric_limits< unsigned int >::digits) +
       (Bits <= std::numeric_limits< unsigned short >::digits) +
       (Bits <= std::numeric_limits< unsigned char >::digits)) );
  };

  template < int BitsIncludingSign >
  struct int_exact_rank_helper   { BOOST_STATIC_CONSTANT( int, rank = 0 ); };
  template < int Bits >
  struct uint_exact_rank_helper  { BOOST_STATIC_CONSTANT( int, rank = 0 ); };

#define BOOST_PRIVATE_INT_EXACT_BUILDER(Type, Rank) \
  template < > \
  struct int_exact_rank_helper<std::numeric_limits< Type >::digits + 1> \
  { BOOST_STATIC_CONSTANT( int, rank = Rank ); }
#define BOOST_PRIVATE_UINT_EXACT_BUILDER(Type, Rank) \
  template < > \
  struct uint_exact_rank_helper<std::numeric_limits< Type >::digits> \
  { BOOST_STATIC_CONSTANT( int, rank = Rank ); }

#if BOOST_HAS_XINT && (BOOST_UXINT_MAX > ULONG_MAX)
  BOOST_PRIVATE_INT_EXACT_BUILDER( xint_t, 1 );
  BOOST_PRIVATE_UINT_EXACT_BUILDER( uxint_t, 1 );
#endif
#if ULONG_MAX > UINT_MAX
  BOOST_PRIVATE_INT_EXACT_BUILDER( long, 2 );
  BOOST_PRIVATE_UINT_EXACT_BUILDER( unsigned long, 2 );
#endif
#if UINT_MAX > USHRT_MAX
  BOOST_PRIVATE_INT_EXACT_BUILDER( int, 3 );
  BOOST_PRIVATE_UINT_EXACT_BUILDER( unsigned, 3 );
#endif
#if USHRT_MAX > UCHAR_MAX
  BOOST_PRIVATE_INT_EXACT_BUILDER( short, 4 );
  BOOST_PRIVATE_UINT_EXACT_BUILDER( unsigned short, 4 );
#endif
  BOOST_PRIVATE_INT_EXACT_BUILDER( signed char, 5 );
  BOOST_PRIVATE_UINT_EXACT_BUILDER( unsigned char, 5 );

#undef BOOST_PRIVATE_INT_EXACT_BUILDER
#undef BOOST_PRIVATE_UINT_EXACT_BUILDER

  //  map an extreme value to a category
  template < intmax_t MaxValue >
  struct int_max_rank_helper
  {
#if BOOST_HAS_XINT
      BOOST_STATIC_CONSTANT( int, extended_ = (MaxValue <=
       boost::integer_traits< xint_t >::const_max) );
#else
      BOOST_STATIC_CONSTANT( int, extended_ = 1 );
#endif
      BOOST_STATIC_CONSTANT( int, rank = (MaxValue > 0) * (extended_ +
       (MaxValue <= boost::integer_traits< long >::const_max) +
       (MaxValue <= boost::integer_traits< int >::const_max) +
       (MaxValue <= boost::integer_traits< short >::const_max) +
       (MaxValue <= boost::integer_traits< signed char >::const_max)) );
  };

  template < intmax_t MinValue >
  struct int_min_rank_helper
  {
#if BOOST_HAS_XINT
      BOOST_STATIC_CONSTANT( int, extended_ = (MinValue >=
       boost::integer_traits< xint_t >::const_min) );
#else
      BOOST_STATIC_CONSTANT( int, extended_ = 1 );
#endif
      BOOST_STATIC_CONSTANT( int, rank = (MinValue < 0) * (extended_ +
       (MinValue >= boost::integer_traits< long >::const_min) +
       (MinValue >= boost::integer_traits< int >::const_min) +
       (MinValue >= boost::integer_traits< short >::const_min) +
       (MinValue >= boost::integer_traits< signed char >::const_min)) );
  };

  template < uintmax_t Value >
  struct uint_max_rank_helper
  {
#if BOOST_HAS_XINT
      BOOST_STATIC_CONSTANT( int, extended_ = (Value <= boost::integer_traits<
       uxint_t >::const_max) );
#else
      BOOST_STATIC_CONSTANT( int, extended_ = 1 );
#endif
      BOOST_STATIC_CONSTANT( int, rank = extended_ +
       (Value <= boost::integer_traits< unsigned long >::const_max) +
       (Value <= boost::integer_traits< unsigned int >::const_max) +
       (Value <= boost::integer_traits< unsigned short >::const_max) +
       (Value <= boost::integer_traits< unsigned char >::const_max) );
  };

  //  convert rank to type, Boost.MPL-style
  template < int Rank, typename Signedness, class Enable = void >
  struct integral_rank_to_type
  {
      BOOST_STATIC_CONSTANT( bool, is_specialized = false );
      // No "signed" nor "type" here
  };

  template < int Rank >
  struct integral_rank_to_type< Rank, signed, typename
   enable_if_c<(lowest_integral_rank <= Rank) && (Rank <=
   highest_integral_rank)>::type >
  {
      BOOST_STATIC_CONSTANT( bool, is_specialized = true );
      BOOST_STATIC_CONSTANT( bool, is_signed = true );
      typedef typename int_least_helper< Rank, signed >::least  type;
  };

  template < int Rank >
  struct integral_rank_to_type< Rank, unsigned, typename
   enable_if_c<(lowest_integral_rank <= Rank) && (Rank <=
   highest_integral_rank)>::type >
  {
      BOOST_STATIC_CONSTANT( bool, is_specialized = true );
      BOOST_STATIC_CONSTANT( bool, is_signed = false );
      typedef typename int_least_helper< Rank, unsigned >::least  type;
  };

} // namespace detail

  //  MPL-compatible integer-mapping class templates  ------------------------//

  //  minimum number of bits
  template < int Bits, typename Signedness >
  struct sized_integral
  {
      BOOST_STATIC_CONSTANT( bool, is_specialized = false );
      BOOST_STATIC_CONSTANT( int, bit_count = Bits );
  };

  template < int BitsIncludingSign >
  struct sized_integral< BitsIncludingSign, signed >
      : detail::integral_rank_to_type<
         detail::int_rank_helper<BitsIncludingSign>::rank, signed >
  {
      BOOST_STATIC_CONSTANT( int, bit_count = BitsIncludingSign );
  };

  template < int Bits >
  struct sized_integral< Bits, unsigned >
      : detail::integral_rank_to_type<
         detail::uint_rank_helper<Bits>::rank, unsigned >
  {
      BOOST_STATIC_CONSTANT( int, bit_count = Bits );
  };

  //  exact number of bits
  template < int Bits, typename Signedness >
  struct exact_integral
  {
      BOOST_STATIC_CONSTANT( bool, is_specialized = false );
      BOOST_STATIC_CONSTANT( int, bit_count = Bits );
  };

  template < int BitsIncludingSign >
  struct exact_integral< BitsIncludingSign, signed >
      : detail::integral_rank_to_type<
         detail::int_exact_rank_helper<BitsIncludingSign>::rank, signed >
  {
      BOOST_STATIC_CONSTANT( int, bit_count = BitsIncludingSign );
  };

  template < int Bits >
  struct exact_integral< Bits, unsigned >
      : detail::integral_rank_to_type<
         detail::uint_exact_rank_helper<Bits>::rank, unsigned >
  {
      BOOST_STATIC_CONSTANT( int, bit_count = Bits );
  };

  //  maximum supported (positive) value, signed
  template < intmax_t MaxValue >
  struct maximum_signed_integral
      : detail::integral_rank_to_type<
         detail::int_max_rank_helper<MaxValue>::rank, signed >
  {
      BOOST_STATIC_CONSTANT( intmax_t, bound = MaxValue );
  };

  //  minimum supported (negative) value
  template < intmax_t MinValue >
  struct minimum_signed_integral
      : detail::integral_rank_to_type<
         detail::int_min_rank_helper<MinValue>::rank, signed >
  {
      BOOST_STATIC_CONSTANT( intmax_t, bound = MinValue );
  };

  //  maximum supported (nonnegative) value, unsigned
  template < uintmax_t Value >
  struct maximum_unsigned_integral
      : detail::integral_rank_to_type<
         detail::uint_max_rank_helper<Value>::rank, unsigned >
  {
      BOOST_STATIC_CONSTANT( uintmax_t, bound = Value );
  };

  //  integer templates specifying number of bits  ---------------------------//

  //  signed
  template< int Bits >   // minimum bits (including sign) required
  struct int_t 
  {
      typedef typename sized_integral<Bits, signed>::type  least;
      typedef typename int_fast_t<least>::fast             fast;
  };

  template< int Bits >   // exact bits (including sign) desired
  struct int_exact_t
  {
      typedef typename exact_integral<Bits, signed>::type  exact;
  };

  //  unsigned
  template< int Bits >   // minimum bits required
  struct uint_t 
  {
      typedef typename sized_integral<Bits, unsigned>::type  least;
      typedef typename int_fast_t<least>::fast               fast;
      // int_fast_t<> works correctly for unsigned too, in spite of the name.
  };

  template< int Bits >   // exact bits desired
  struct uint_exact_t
  {
      typedef typename exact_integral<Bits, unsigned>::type  exact;
  };

  //  integer templates specifying extreme value  ----------------------------//

  //  signed
  template< intmax_t MaxValue >   // maximum value to require support
  struct int_max_value_t 
  {
      typedef typename maximum_signed_integral<MaxValue>::type  least;
      typedef typename int_fast_t<least>::fast                  fast;
  };

  template< intmax_t MinValue >   // minimum value to require support
  struct int_min_value_t 
  {
      typedef typename minimum_signed_integral<MinValue>::type  least;
      typedef typename int_fast_t<least>::fast                  fast;
  };

  //  unsigned
  template< uintmax_t Value >   // maximum value to require support
  struct uint_value_t 
  {
      typedef typename maximum_unsigned_integral<Value>::type  least;
      typedef typename int_fast_t<least>::fast                 fast;
  };


} // namespace boost

#endif  // BOOST_INTEGER_HPP
