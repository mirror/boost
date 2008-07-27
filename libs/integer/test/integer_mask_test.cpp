//  boost integer_mask.hpp test program  -------------------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version including documentation.

//  Revision History
//  27 Jul 2008  Changed tests to use the unit-test system; added
//               extended-integer support. (Daryle Walker)
//  23 Sep 2001  Initial version (Daryle Walker)

#define BOOST_TEST_MODULE  "Integer mask tests"
#include <boost/test/unit_test.hpp>  // unit testing framework

#include <boost/cstdint.hpp>               // for boost::uintmax_t
#include <boost/integer/integer_mask.hpp>  // for boost::high_bit_mask_t, etc.
#include <boost/limits.hpp>                // for std::numeric_limits
#include <boost/mpl/assert.hpp>            // for BOOST_MPL_ASSERT_RELATION
#include <boost/mpl/range_c.hpp>           // for boost::mpl::range_c

#include <cstddef>   // for std::size_t


// Custom types/templates, helper functions, and objects
namespace
{

// A big one
boost::uintmax_t const  one = 1u;

// List the ranges of template parameters tests (ranges are half-open)
int const  max_offset = std::numeric_limits<boost::uintmax_t>::digits;

typedef boost::mpl::range_c<std::size_t, 0, max_offset>     high_bit_offsets;
typedef boost::mpl::range_c<std::size_t, 1, max_offset + 1>  low_bit_lengths;

}  // unnamed namespace


// Check the various integer-valued bit-masks
BOOST_AUTO_TEST_SUITE( integer_mask_tests )

// Check the bit-masks of one offset bit
BOOST_AUTO_TEST_CASE_TEMPLATE( high_bit_mask_test, T, high_bit_offsets )
{
    BOOST_MPL_ASSERT_RELATION( boost::high_bit_mask_t<T::value>::high_bit, ==,
     (one << T::value) );
    BOOST_MPL_ASSERT_RELATION( boost::high_bit_mask_t<T::value>::high_bit_fast,
     ==, (one << T::value) );
}

// Check the bit-masks of a block of low-valued bits
BOOST_AUTO_TEST_CASE_TEMPLATE( low_bits_mask_test, T, low_bit_lengths )
{
    // One can express (2^x - 1) in two ways
    // 1. (1 << x) - 1
    // 2. (1 << (x-1)) | ((1 << (x-1)) - 1)
    // Since unsigneds have modulo arithmetic, [1] gives the right answer even
    // when x is the number of bits in the register.  However, that last case
    // gives warnings about the sole bit flowing past the register.  Applying
    // distributive property backwards gives [2], which works without overflow.
    BOOST_MPL_ASSERT_RELATION( boost::low_bits_mask_t<T::value>::sig_bits, ==,
     (one << ( T::value - 1u )) | (( one << (T::value - 1u) ) - 1u) );
    BOOST_MPL_ASSERT_RELATION( boost::low_bits_mask_t<T::value>::sig_bits_fast,
     ==, (one << ( T::value - 1u )) | (( one << (T::value - 1u) ) - 1u) );
}

BOOST_AUTO_TEST_SUITE_END()

// Verification of bugs and their fixes
BOOST_AUTO_TEST_SUITE( bug_fix_tests )

BOOST_AUTO_TEST_SUITE_END()
