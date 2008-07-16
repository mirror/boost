//  Boost integer_fwd.hpp header file  ---------------------------------------//

//  (C) Copyright Dave Abrahams and Daryle Walker 2001. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

#ifndef BOOST_INTEGER_FWD_HPP
#define BOOST_INTEGER_FWD_HPP

#include <climits>  // for UCHAR_MAX, etc.
#include <cstddef>  // for std::size_t

#include <boost/config.hpp>   // for BOOST_NO_INTRINSIC_WCHAR_T
#include <boost/cstdint.hpp>  // for boost::uintmax_t, intmax_t
#include <boost/limits.hpp>   // for std::numeric_limits


namespace boost
{


//  From <boost/cstdint.hpp>  ------------------------------------------------//

// Only has typedefs or using statements, with #conditionals

// ALERT: the forward declarations of items in <boost/integer.hpp> need items
// from this header.  That means that <boost/cstdint.hpp> cannot #include this
// forwarding header, to avoid infinite recursion!  One day, maybe
// boost::uintmax_t and boost::intmax_t could be segregated into their own
// header file (which can't #include this header), <boost/integer.hpp> will use
// that header, and <boost/cstdint.hpp> could refer to <boost/integer.hpp>.


//  From <boost/integer_traits.hpp>  -----------------------------------------//

template < class T >
    class integer_traits;

template <  >
    class integer_traits< bool >;

template <  >
    class integer_traits< char >;

template <  >
    class integer_traits< signed char >;

template <  >
    class integer_traits< unsigned char >;

#ifndef BOOST_NO_INTRINSIC_WCHAR_T
template <  >
    class integer_traits< wchar_t >;
#endif

template <  >
    class integer_traits< short >;

template <  >
    class integer_traits< unsigned short >;

template <  >
    class integer_traits< int >;

template <  >
    class integer_traits< unsigned int >;

template <  >
    class integer_traits< long >;

template <  >
    class integer_traits< unsigned long >;

#ifdef ULLONG_MAX
template <  >
    class integer_traits<  ::boost::long_long_type>;

template <  >
    class integer_traits<  ::boost::ulong_long_type >;
#endif


//  From <boost/integer.hpp>  ------------------------------------------------//

template < typename BaseInt >
    struct fast_integral;

template < typename LeastInt >
    struct int_fast_t;

template < int Bits, typename Signedness >
    struct sized_integral;

template < int Bits, typename Signedness >
    struct exact_integral;

template < intmax_t MaxValue >
    struct maximum_signed_integral;

template < intmax_t MinValue >
    struct minimum_signed_integral;

template < uintmax_t Value >
    struct maximum_unsigned_integral;

template< int Bits >
    struct int_t;

template< int Bits >
    struct int_exact_t;

template< int Bits >
    struct uint_t;

template< int Bits >
    struct uint_exact_t;

template< intmax_t MaxValue >
    struct int_max_value_t;

template< intmax_t MinValue >
    struct int_min_value_t;

template< uintmax_t Value >
    struct uint_value_t;


//  From <boost/integer/integer_mask.hpp>  -----------------------------------//

template < std::size_t Bit >
    struct high_bit_mask_t;

template < std::size_t Bits >
    struct low_bits_mask_t;

template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned char>::digits >;

#if USHRT_MAX > UCHAR_MAX
template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned short>::digits >;
#endif

#if UINT_MAX > USHRT_MAX
template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned int>::digits >;
#endif

#if ULONG_MAX > UINT_MAX
template <  >
    struct low_bits_mask_t< ::std::numeric_limits<unsigned long>::digits >;
#endif


//  From <boost/integer/static_log2.hpp>  ------------------------------------//

template < unsigned long Value >
    struct static_log2;

template <  >
    struct static_log2< 0ul >;


//  From <boost/integer/static_min_max.hpp>  ---------------------------------//

template < long Value1, long Value2 >
    struct static_signed_min;

template < long Value1, long Value2 >
    struct static_signed_max;

template < unsigned long Value1, unsigned long Value2 >
    struct static_unsigned_min;

template < unsigned long Value1, unsigned long Value2 >
    struct static_unsigned_max;


}  // namespace boost


#endif  // BOOST_INTEGER_FWD_HPP
