//  Boost integer/integer_mask.hpp header file  ------------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_INTEGER_MASK_HPP
#define BOOST_INTEGER_INTEGER_MASK_HPP

#include <boost/integer_fwd.hpp>  // self include

#include <boost/config.hpp>             // for BOOST_STATIC_CONSTANT
#include <boost/cstdint.hpp>            // for boost::uintmax_t
#include <boost/integer.hpp>            // for boost::sized_integral
#include <boost/limits.hpp>             // for std::numeric_limits
#include <boost/mpl/and.hpp>            // for boost::mpl::and_
#include <boost/mpl/bitwise.hpp>        // for boost::mpl::bitor_, shift_left
#include <boost/mpl/bool.hpp>           // for boost::mpl::true_
#include <boost/mpl/comparison.hpp>     // for boost::mpl::greater_equal, etc.
#include <boost/mpl/empty_base.hpp>     // for boost::mpl::empty_base
#include <boost/mpl/if.hpp>             // for boost::mpl::if_
#include <boost/mpl/int.hpp>            // for boost::mpl::int_
#include <boost/mpl/integral_c.hpp>     // for boost::integral_c
#include <boost/mpl/next_prior.hpp>     // for boost::mpl::next, prior
#include <boost/utility/enable_if.hpp>  // for boost::enable_if

#include <cstddef>  // for std::size_t


namespace boost
{
namespace detail
{

//  Helper templates  --------------------------------------------------------//

template < int Bits >
struct hi_integer_mask_builder1
{
    typedef boost::mpl::int_<Bits>  bit_count_type;

    typedef typename boost::mpl::next<bit_count_type>::type
      mask_length_type;
    typedef boost::sized_integral<mask_length_type::value, unsigned>
      mask_type;

    typedef boost::mpl::integral_c<typename mask_type::type, 1>  one_type;
    typedef boost::mpl::shift_left<one_type, bit_count_type>  result_type;
};

template < int Bits >
struct hi_integer_mask_builder2
{
    typedef boost::mpl::int_<Bits>  bit_count_type;

    typedef boost::mpl::greater_equal< bit_count_type, boost::mpl::int_<0> >
      lo_bound_type;
    typedef boost::mpl::less< bit_count_type,
     boost::mpl::int_<std::numeric_limits<boost::uintmax_t>::digits> >
      hi_bound_type;
    typedef boost::mpl::and_<lo_bound_type, hi_bound_type>  count_valid_type;
};

template < int Bits, class Enable = void >
struct hi_integer_mask_builder3
{
    BOOST_STATIC_CONSTANT( bool, is_specialized = false );
};

template < int Bits >
struct hi_integer_mask_builder3< Bits, typename boost::enable_if<typename
 hi_integer_mask_builder2<Bits>::count_valid_type>::type >
    : hi_integer_mask_builder1<Bits>::result_type
{
    BOOST_STATIC_CONSTANT( bool, is_specialized = true );
};

template < int Bits >
struct lo_integer_mask_builder1
{
    typedef boost::mpl::int_<Bits>  bit_count_type;

    typedef typename boost::mpl::prior<bit_count_type>::type
      shift_length_type;
    typedef boost::sized_integral<bit_count_type::value, unsigned>
      mask_type;

    typedef boost::mpl::integral_c<typename mask_type::type, 1>  one_type;
    typedef boost::mpl::shift_left<one_type, shift_length_type>
      high_bit_type;
    typedef typename boost::mpl::prior<high_bit_type>::type  low_bits_type;
    typedef boost::mpl::bitor_<high_bit_type, low_bits_type>  result_type;
};

template <  >
struct lo_integer_mask_builder1< 0 >
{
    // Let's not deal with negative interim values....
    typedef boost::mpl::integral_c<unsigned char, 0u>  result_type;
};

template < int Bits >
struct lo_integer_mask_builder2
{
    typedef boost::mpl::int_<Bits>  bit_count_type;

    typedef boost::mpl::greater_equal< bit_count_type, boost::mpl::int_<0> >
      lo_bound_type;
    typedef boost::mpl::less_equal< bit_count_type,
     boost::mpl::int_<std::numeric_limits<boost::uintmax_t>::digits> >
      hi_bound_type;
    typedef boost::mpl::and_<lo_bound_type, hi_bound_type>  count_valid_type;
};

template <  >
struct lo_integer_mask_builder2< 0 >
{
    typedef boost::mpl::true_  count_valid_type;
};

template < int Bits, class Enable = void >
struct lo_integer_mask_builder3
{
    BOOST_STATIC_CONSTANT( bool, is_specialized = false );
    // No MPL Integral Constant to inherit from
};

template < int Bits >
struct lo_integer_mask_builder3< Bits, typename enable_if<typename
 lo_integer_mask_builder2<Bits>::count_valid_type>::type >
    : lo_integer_mask_builder1<Bits>::result_type
{
    BOOST_STATIC_CONSTANT( bool, is_specialized = true );
};

} // namespace detail


//  MPL-compatible integer mask class templates  -----------------------------//

// Displaced single-bit mask, 1 << Offset, 0 <= Offset < BitLengthOf(uintmax_t)
template < int Offset >
struct integer_hi_mask
    : detail::hi_integer_mask_builder3<Offset>
{
    BOOST_STATIC_CONSTANT( int, bit_offset = Offset );
};

// Lowest bit-group mask, 2**Length - 1, 0 <= Length <= BitLengthOf(uintmax_t)
template < int Length >
struct integer_lo_mask
    : detail::lo_integer_mask_builder3<Length>
{
    BOOST_STATIC_CONSTANT( int, bit_count = Length );
};


//  Specified single-bit mask class declaration  -----------------------------//
//  (Lowest bit starts counting at 0.)

template < std::size_t Bit >
class high_bit_mask_t
{
    typedef integer_hi_mask<Bit>  impl_type;

public:
    typedef typename impl_type::value_type   least;
    typedef typename int_fast_t<least>::fast  fast;

    BOOST_STATIC_CONSTANT( least, high_bit = impl_type::value );
    BOOST_STATIC_CONSTANT( fast, high_bit_fast = impl_type::value );

    BOOST_STATIC_CONSTANT( std::size_t, bit_position = impl_type::bit_offset );

};  // boost::high_bit_mask_t


//  Specified bit-block mask class declaration  ------------------------------//
//  Makes masks for the lowest N bits

template < std::size_t Bits >
class low_bits_mask_t
{
    typedef integer_lo_mask<Bits>  impl_type;

public:
    typedef typename impl_type::value_type   least;
    typedef typename int_fast_t<least>::fast  fast;

    BOOST_STATIC_CONSTANT( least, sig_bits = impl_type::value );
    BOOST_STATIC_CONSTANT( fast, sig_bits_fast = impl_type::value );

    BOOST_STATIC_CONSTANT( std::size_t, bit_count = impl_type::bit_count );

};  // boost::low_bits_mask_t


}  // namespace boost


#endif  // BOOST_INTEGER_INTEGER_MASK_HPP
