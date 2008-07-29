//  boost integer_mask.hpp test program  -------------------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  29 Jul 2008  Added MPL-compatible variants of the integer-mask templates.
//               (Daryle Walker)
//  27 Jul 2008  Changed tests to use the unit-test system; added
//               extended-integer support. (Daryle Walker)
//  23 Sep 2001  Initial version (Daryle Walker)

#define BOOST_TEST_MODULE  "Integer mask tests"
#include <boost/test/unit_test.hpp>  // unit testing framework

#include <boost/cstdint.hpp>               // for boost::uintmax_t
#include <boost/integer/integer_mask.hpp>  // for boost::high_bit_mask_t, etc.
#include <boost/limits.hpp>                // for std::numeric_limits
#include <boost/mpl/assert.hpp>            // for BOOST_MPL_ASSERT_RELATION,etc.
#include <boost/mpl/bool.hpp>              // for boost::mpl::bool_
#include <boost/mpl/bitwise.hpp>           // for boost::mpl::bitor_, shift_left
#include <boost/mpl/equal_to.hpp>          // for boost::mpl::equal_to
#include <boost/mpl/int.hpp>               // for boost::mpl::int_
#include <boost/mpl/integral_c.hpp>        // for boost::mpl::integral_c
#include <boost/mpl/next_prior.hpp>        // for boost::mpl::prior
#include <boost/mpl/range_c.hpp>           // for boost::mpl::range_c

#include <cstddef>   // for std::size_t
#include <ios>       // for std::hex
#include <iostream>  // for std::cout
#include <ostream>   // for std::endl


// Control if events will be printed conventionally, or just logged.
#ifndef CONTROL_SHOW_TYPES
#define CONTROL_SHOW_TYPES  0
#endif

// Logging
#if CONTROL_SHOW_TYPES
#define PRIVATE_SHOW_MESSAGE( m )  std::cout << m << std::endl
#else
#define PRIVATE_SHOW_MESSAGE( m )  BOOST_TEST_MESSAGE( m )
#endif


// Custom types/templates, helper functions, and objects
namespace
{

// List the ranges of template parameters tests (ranges are half-open)
int const  max_offset = std::numeric_limits<boost::uintmax_t>::digits;

typedef boost::mpl::range_c<int, 0, max_offset>             high_bit_offsets;
typedef boost::mpl::range_c<int, 0, max_offset + 1>          low_bit_lengths;
typedef boost::mpl::range_c<int, 1, max_offset + 1>  special_low_bit_lengths;

// List a range with out-of-service values
typedef boost::mpl::range_c<int, -10, max_offset + 11>  wild_bit_lengths;

// Use SFINAE to check if a particular parameter is supported
template < typename ValueT, template<ValueT> class Tmpl, ValueT Value >
bool
print_out_template( Tmpl<Value> const &, ValueT setting, char const
 *template_name, typename Tmpl<Value>::type *unused = 0 )
{
    // Too bad the type-id expression couldn't use the compact form "*unused",
    // but type-ids of dereferenced null pointers throw by order of C++ 2003,
    // sect. 5.2.8, para. 2 (although the result is not conceptually needed).
    PRIVATE_SHOW_MESSAGE( "There is an " << template_name << "<" << setting <<
     "> specialization with type '" << typeid(typename
     Tmpl<Value>::value_type).name() << "' and value '" << std::hex <<
     Tmpl<Value>::value << "'." );
    return true;
}

template < typename ValueT, typename T >
bool
print_out_template( T const &, ValueT setting, char const *template_name )
{
    PRIVATE_SHOW_MESSAGE( "There is no " << template_name << "<" << setting <<
     "> specialization." );
    return false;
}

}  // unnamed namespace


// Check the various integer-valued bit-masks
BOOST_AUTO_TEST_SUITE( integer_mask_tests )

// Check the bit-masks of one offset bit
BOOST_AUTO_TEST_CASE_TEMPLATE( high_bit_mask_test, T, high_bit_offsets )
{
    typedef boost::mpl::integral_c<typename
     boost::high_bit_mask_t<T::value>::least, 1u>   one_type;
    typedef boost::mpl::shift_left<one_type, T>  result_type;

    BOOST_MPL_ASSERT_RELATION( boost::high_bit_mask_t<T::value>::high_bit, ==,
     result_type::value );
    BOOST_MPL_ASSERT_RELATION( boost::high_bit_mask_t<T::value>::high_bit_fast,
     ==, result_type::value );
}

// Check the bit-masks of a block of low-valued bits, non-zero block-lengths
BOOST_AUTO_TEST_CASE_TEMPLATE( low_bits_mask_test, T, special_low_bit_lengths )
{
    // One can express (2^x - 1) in two ways
    // 1. (1 << x) - 1
    // 2. (1 << (x-1)) | ((1 << (x-1)) - 1)
    // Since unsigneds have modulo arithmetic, [1] gives the right answer even
    // when x is the number of bits in the register.  However, that last case
    // gives warnings about the sole bit flowing past the register.  Applying
    // distributive property backwards gives [2], which works without overflow.
    typedef typename boost::mpl::prior<T>::type                  shift_type;
    typedef boost::mpl::integral_c<typename
     boost::low_bits_mask_t<T::value>::least, 1u>                  one_type;
    typedef boost::mpl::shift_left<one_type, shift_type>      high_bit_type;
    typedef typename boost::mpl::prior<high_bit_type>::type   low_bits_type;
    typedef boost::mpl::bitor_<high_bit_type, low_bits_type>    result_type;

    BOOST_MPL_ASSERT_RELATION( boost::low_bits_mask_t<T::value>::sig_bits, ==,
     result_type::value );
    BOOST_MPL_ASSERT_RELATION( boost::low_bits_mask_t<T::value>::sig_bits_fast,
     ==, result_type::value );
}

// Check the bit-masks of a block of low-valued bits, zero block-length
BOOST_AUTO_TEST_CASE( special_low_bits_mask_test )
{
    // Just like "low_bits_mask_test" above, except that the shifts are negative
    // when the bit-count is zero.  That causes a lot of warnings and errors, so
    // special-case that bit-count.
    BOOST_MPL_ASSERT_RELATION( boost::low_bits_mask_t<0u>::sig_bits, ==, 0 );
    BOOST_MPL_ASSERT_RELATION(boost::low_bits_mask_t<0u>::sig_bits_fast, ==, 0);
}

// Check the specialization type status of given bit-offsets/lengths
BOOST_AUTO_TEST_CASE_TEMPLATE( confirm_bounds_test, T, wild_bit_lengths )
{
    typedef boost::integer_hi_mask<T::value>                    hi_type;
    typedef boost::mpl::int_<hi_type::bit_offset>        hi_offset_type;
    typedef boost::mpl::bool_<hi_type::is_specialized>  special_hi_type;

    BOOST_MPL_ASSERT( (boost::mpl::equal_to< hi_offset_type, T >) );
    BOOST_MPL_ASSERT( (boost::mpl::equal_to< special_hi_type,
     boost::mpl::bool_<(T::value >= 0) && (T::value < max_offset)> >) );
    BOOST_CHECK_EQUAL( print_out_template(hi_type(), hi_offset_type::value,
     "integer_hi_mask"), special_hi_type::value );

    typedef boost::integer_lo_mask<T::value>                    lo_type;
    typedef boost::mpl::int_<lo_type::bit_count>         lo_length_type;
    typedef boost::mpl::bool_<lo_type::is_specialized>  special_lo_type;

    BOOST_MPL_ASSERT( (boost::mpl::equal_to< lo_length_type, T >) );
    BOOST_MPL_ASSERT( (boost::mpl::equal_to< special_lo_type,
     boost::mpl::bool_<(T::value >= 0) && (T::value <= max_offset)> >) );
    BOOST_CHECK_EQUAL( print_out_template(lo_type(), lo_length_type::value,
     "integer_lo_mask"), special_lo_type::value );
}

BOOST_AUTO_TEST_SUITE_END()

// Verification of bugs and their fixes
BOOST_AUTO_TEST_SUITE( bug_fix_tests )

BOOST_AUTO_TEST_SUITE_END()
