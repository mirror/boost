//  boost integer.hpp test program  ------------------------------------------//

//  Copyright Beman Dawes 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org/libs/integer for documentation.

//  Revision History
//   14 Jul 08  Improved testing of fast-integer template. (Daryle Walker)
//   13 Jul 08  Modernized tests w/ MPL instead of giant macros (Daryle Walker)
//   07 Jul 08  Changed tests to use the unit-test system (Daryle Walker)
//   04 Oct 01  Added tests for new templates; rewrote code (Daryle Walker)
//   10 Mar 01  Boost Test Library now used for tests (Beman Dawes)
//   31 Aug 99  Initial version

#define BOOST_TEST_MODULE  "Integer size-selection tests"

#include <boost/test/unit_test.hpp>           // unit testing framework
#include <boost/test/test_case_template.hpp>  // ..BOOST_AUTO_TEST_CASE_TEMPLATE

#include <boost/config.hpp>   // for BOOST_NO_USING_TEMPLATE
#include <boost/integer.hpp>  // for boost::int_t, boost::uint_t, etc.
#include <boost/limits.hpp>   // for std::numeric_limits

#include <boost/mpl/arithmetic.hpp>      // for boost::mpl::plus, divides
#include <boost/mpl/assert.hpp>          // for BOOST_MPL_ASSERT_RELATION, etc.
#include <boost/mpl/back.hpp>            // for boost::mpl::back
#include <boost/mpl/copy.hpp>            // for boost::mpl::copy
#include <boost/mpl/front_inserter.hpp>  // for boost::mpl::front_inserter
#include <boost/mpl/integral_c.hpp>      // for boost::mpl::integral_c
#include <boost/mpl/joint_view.hpp>      // for boost::mpl::joint_view
#include <boost/mpl/pop_back.hpp>        // for boost::mpl::pop_back
#include <boost/mpl/push_back.hpp>       // for boost::mpl::push_back 
#include <boost/mpl/push_front.hpp>      // for boost::mpl::push_front
#include <boost/mpl/sort.hpp>            // for boost::mpl::sort
#include <boost/mpl/transform.hpp>       // for boost::mpl::transform
#include <boost/mpl/transform_view.hpp>  // for boost::mpl::transform_view
#include <boost/mpl/unpack_args.hpp>     // for boost::mpl::unpack_args
#include <boost/mpl/vector.hpp>          // for boost::mpl::vector
#include <boost/mpl/zip_view.hpp>        // for boost::mpl::zip_view

#include <boost/type_traits/is_same.hpp>      // for boost::is_same
#include <boost/type_traits/make_signed.hpp>  // for boost::make_signed

#include <climits>   // for ULONG_MAX, LONG_MAX, LONG_MIN, etc.
#include <iostream>  // for std::cout
#include <ostream>   // for std::endl
#include <typeinfo>  // for std::type_info


// Control what the "fast" specialization of "short" is
#ifndef CONTROL_FAST_SHORT
#define CONTROL_FAST_SHORT  long
#endif

// Control if the names of the types for each version
// of the integer templates will be printed.
#ifndef CONTROL_SHOW_TYPES
#define CONTROL_SHOW_TYPES  0
#endif


// If specializations have not already been done, then we can confirm
// the effects of the "fast" types by making a specialization.  If there
// is a specialization for "short," make sure that CONTROL_FAST_SHORT
// is set to a type distinct from "short" and the default implementation.
namespace boost
{
    template < >
    struct int_fast_t< short >
    {
        typedef CONTROL_FAST_SHORT  fast;
    };
}


// Logging
#if CONTROL_SHOW_TYPES
#define PRIVATE_SHOW_MESSAGE( m )  std::cout << m << std::endl
#else
#define PRIVATE_SHOW_MESSAGE( m )  BOOST_TEST_MESSAGE( m )
#endif


// Custom types/templates, helper functions, and objects
namespace
{

// List the built-in integral types, excluding the ones that are strong-typedefs
// of a lower type.
typedef boost::mpl::vector<
    unsigned char
#if USHRT_MAX > UCHAR_MAX
    , unsigned short
#endif
#if UINT_MAX > USHRT_MAX
    , unsigned int
#endif
#if ULONG_MAX > UINT_MAX
    , unsigned long
#endif
>  distinct_unsigned_types;

typedef boost::mpl::transform<
    distinct_unsigned_types,
    boost::make_signed< boost::mpl::_1 >
>::type  distinct_signed_types;

// List the digit counts for each integral type
class dibc_helper
{
    template < typename T >
    struct type_to_digit_count
        : boost::mpl::integral_c< int, std::numeric_limits<T>::digits >
    {};

public:
    typedef boost::mpl::transform<
        distinct_unsigned_types,
        type_to_digit_count< boost::mpl::_1 >
    >::type  type;
};

typedef dibc_helper::type  distinct_integral_bit_counts;

// Make list of bit counts between each offical point, plus CHAR_BIT/2
typedef boost::mpl::transform_view<
    boost::mpl::zip_view<
        boost::mpl::vector<
            boost::mpl::push_front<
                boost::mpl::pop_back< distinct_integral_bit_counts >::type,
                boost::mpl::integral_c< int, 0 >
            >::type,
            distinct_integral_bit_counts
        >
    >,
    boost::mpl::unpack_args<
        boost::mpl::divides<
            boost::mpl::plus< boost::mpl::_1, boost::mpl::_2 >,
            boost::mpl::integral_c< int, 2 >
        >
    >
>  median_bit_counts;

// Maximum number of bits allowed
int const   intmax_bits = boost::mpl::back<distinct_integral_bit_counts>::type::value;
    // should be std::numeric_limits<boost::intmax_t>::digits + 1
int const  uintmax_bits = intmax_bits;
    // should be std::numeric_limits<boost::uintmax_t>::digits

// Make master lists including an outlier beyond all valid bit counts
typedef boost::mpl::sort<
    boost::mpl::copy<
        boost::mpl::joint_view<
            distinct_integral_bit_counts,
            median_bit_counts
        >,
        boost::mpl::front_inserter<
            boost::mpl::vector<
                boost::mpl::integral_c<int, uintmax_bits + 1>
            >
        >
    >::type
>::type  bits_list;

// Remove the outlier when all bits counts must be valid
typedef boost::mpl::pop_back<bits_list>::type  valid_bits_list;

// Replace the maximum bit count with one less, so left-shifting by a stored
// value doesn't give an invalid result
typedef boost::mpl::push_back<
    boost::mpl::pop_back< valid_bits_list >::type,
    boost::mpl::integral_c< int, uintmax_bits - 1 >
>::type  valid_to_increase_ubits_list;

// Do it again for signed types since they have one-less bit to use for the
// mantissa (don't want to shift into the sign bit)
typedef boost::mpl::push_back<
    boost::mpl::pop_back< valid_bits_list >::type,
    boost::mpl::integral_c< int, intmax_bits - 2 >
>::type  valid_to_increase_sbits_list;

}  // unnamed namespace


// Check the processor-optimzed type system
BOOST_AUTO_TEST_SUITE( optimized_type_tests )

// Check the optimzed type override of a given type
BOOST_AUTO_TEST_CASE( fast_type_test )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using std::numeric_limits;
#else
    using namespace std;
#endif

    typedef short                               least_type;
    typedef boost::int_fast_t<least_type>::fast  fast_type;
    typedef numeric_limits<least_type>          least_limits;
    typedef numeric_limits<fast_type>            fast_limits;

    BOOST_MPL_ASSERT_RELATION( (boost::is_same<least_type, fast_type>::value),
     ==, false );
    BOOST_MPL_ASSERT_RELATION( fast_limits::is_specialized, ==, true );
    BOOST_MPL_ASSERT_RELATION( fast_limits::is_signed &&
     fast_limits::is_bounded, ==, true );
    BOOST_MPL_ASSERT_RELATION( fast_limits::radix, ==, 2 );
    BOOST_MPL_ASSERT_RELATION( fast_limits::digits, >=, least_limits::digits );
}

BOOST_AUTO_TEST_SUITE_END()

// Check if given types can support given size parameters
BOOST_AUTO_TEST_SUITE( show_type_tests )

// Check the specialization type status of given bit lengths
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_lengths_test, T, valid_bits_list )
{
    // This test is supposed to replace the following printouts given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for N := 32 downto 0
    //      cout << "Type '" << Template << "<" N << ">::" << Type << "' is '"
    //      << typeid(Template<N>::Type).name << ".'\n"
    //  end for
    // end Routine
    // with Template = {int_t, uint_t}; Type = {least, fast}
    // But now we'll use template meta-programming instead of macros.  The limit
    // of type-lists is usually less than 32 (not to mention 64) elements, so we
    // have to take selected values.  The only interesting part is if the bit
    // count is too large, and we can't check that yet.
#ifndef BOOST_NO_USING_TEMPLATE
    using std::numeric_limits;
    using boost::int_t;
    using boost::uint_t;
#else
    using namespace std;
    using namespace boost;
#endif

    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     int_t<T::value>::least>::digits, >=, T::value - 1 );
    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     int_t<T::value>::fast>::digits, >=, T::value - 1 );
    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     uint_t<T::value>::least>::digits, >=, T::value );
    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     uint_t<T::value>::fast>::digits, >=, T::value );
}

// Check size comparisons of given value support, unsigned
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_shifted_unsigned_values_test, T,
 valid_to_increase_ubits_list )
{
    // This test is supposed to replace the following printouts given in
    // puesdo-code by:
    // Routine: Type
    //  for N := 30 downto 0
    //      cout << "Type '" << uint_value_t << "<" (1ul << N) << ">::" << Type
    //       << "' is '"<< typeid(uint_value_t<(1ul << N)>::Type).name << ".'\n"
    //  end for
    // end Routine
    // with Type = {least, fast}
    // But now we'll use template meta-programming instead of macros.  The limit
    // of type-lists is usually less than 32 (not to mention 64) elements, so we
    // have to take selected values.  The interesting parts are where N is the
    // length of a integral type, so 1 << N would have to fit in the next larger
    // type.  (This is why N can't be more than bitlength(uintmax_t) - 1.)
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::is_same;
    using boost::uint_value_t;
    using boost::uint_t;
#else
    using namespace boost;
#endif

    unsigned long const  one = 1u;
    int const            count = T::value;

    BOOST_MPL_ASSERT( (is_same<typename uint_value_t<(one << (count -
     2))>::least, typename uint_t<count - 1>::least>::value) );
    BOOST_MPL_ASSERT( (is_same<typename uint_value_t<(one << (count -
     1))>::least, typename uint_t<count>::least>::value) );
    BOOST_MPL_ASSERT( (is_same<typename uint_value_t<(one << count)>::least,
     typename uint_t<count + 1>::least>::value) );
}

// Check size comparisons of given value support, signed
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_shifted_signed_values_test, T,
 valid_to_increase_sbits_list )
{
    // This test is supposed to replace the following printouts given in
    // puesdo-code by:
    // Routine: Type
    //  for N := 30 downto 0
    //      cout << "Type '" << int_max_value_t << "<" +(1ul << N) << ">::" <<
    //       Type << "' is '" << typeid(int_max_value_t<+(1ul << N)>::Type).name
    //       << ".'\n"
    //      cout << "Type '" << int_min_value_t << "<" -(1ul << N) << ">::" <<
    //       Type << "' is '" << typeid(int_min_value_t<-(1ul << N)>::Type).name
    //       << ".'\n"
    //  end for
    // end Routine
    // with Type = {least, fast}
    // But now we'll use template meta-programming instead of macros.  The limit
    // of type-lists is usually less than 32 (not to mention 64) elements, so we
    // have to take selected values.  The interesting parts are where N is the
    // length of a integral type, so 1 << N would have to fit in the next larger
    // type.  (This is why N can't be more than bitlength(intmax_t) - 1.  Note
    // that bitlength(intmax_t) + 1 == bitlength(uintmax_t).)
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::is_same;
    using boost::int_max_value_t;
    using boost::int_t;
    using boost::int_min_value_t;
#else
    using namespace boost;
#endif

    long const  one = 1;
    int const   count = T::value;

    BOOST_MPL_ASSERT( (is_same<typename int_max_value_t<+(one << (count -
     2))>::least, typename int_t<count - 1>::least>::value) );
    BOOST_MPL_ASSERT( (is_same<typename int_min_value_t<-(one << (count -
     2))>::least, typename int_t<count - 1>::least>::value) );

    BOOST_MPL_ASSERT( (is_same<typename int_max_value_t<+(one << (count -
     1))>::least, typename int_t<count>::least>::value) );
    BOOST_MPL_ASSERT( (is_same<typename int_min_value_t<-(one << (count -
     1))>::least, typename int_t<count>::least>::value) );

    BOOST_MPL_ASSERT( (is_same<typename int_max_value_t<+(one << count)>::least,
     typename int_t<count + 1>::least>::value) );
    BOOST_MPL_ASSERT( (is_same<typename int_min_value_t<-(one << count)>::least,
     typename int_t<count + 1>::least>::value) );
}

BOOST_AUTO_TEST_SUITE_END()

// Check if given constants can fit in given types
BOOST_AUTO_TEST_SUITE( fit_type_tests )

// Check if large value can fit its minimum required size, by size
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_masked_values_test, T,
 valid_bits_list )
{
    // This test is supposed to replace the following checks given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for ( N = 32, V = Template:Max ; N >= 0 ; --N, V >>= 1 )
    //      Confirm( static_cast<typename Template<N>::Type>(V) == V );
    //  end for
    // end Routine
    // with Template = {int_t, uint_t}; Type = {least, fast};
    //      Template:Max = { LONG_MAX for int_t, ULONG_MAX for uint_t }
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::uint_t;
    using boost::int_t;
#else
    using namespace boost;
#endif

    int const            count = T::value, shift = uintmax_bits - count;
    unsigned long const  value_u = ULONG_MAX >> shift;
    long const           value_s = LONG_MAX >> shift;

    BOOST_CHECK_EQUAL( typename uint_t<count>::least(value_u), value_u );
    BOOST_CHECK_EQUAL( typename uint_t<count - 1>::least(value_u >> 1), value_u
     >> 1 );
    BOOST_CHECK_EQUAL( typename uint_t<count>::fast(value_u), value_u );
    BOOST_CHECK_EQUAL( typename uint_t<count - 1>::fast(value_u >> 1), value_u
     >> 1 );

    BOOST_CHECK_EQUAL( typename int_t<count>::least(value_s), value_s );
    BOOST_CHECK_EQUAL( typename int_t<count - 1>::least(value_s >> 1), value_s
     >> 1 );
    BOOST_CHECK_EQUAL( typename int_t<count>::fast(value_s), value_s );
    BOOST_CHECK_EQUAL( typename int_t<count - 1>::fast(value_s >> 1), value_s >>
     1 );
}

// Check if large value can fit its minimum required size, by value
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_shifted_values_test, T,
 valid_to_increase_ubits_list )
{
    // This test is supposed to replace the following checks given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for ( N = 0, V = Template:Extreme ; N < 32 ; ++N, V >>= 1 )
    //      Confirm( static_cast<typename Template<V>::Type>(V) == V );
    //  end for
    // end Routine
    // with Template = {uint_value_t, int_max_value_t, int_min_value_t}; Type =
    //      {least, fast}; Template:Extreme = { LONG_MIN for int_min_value_t,
    //      LONG_MAX for int_max_value_t, ULONG_MAX for uint_value_t }
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::uint_value_t;
    using boost::int_max_value_t;
    using boost::int_min_value_t;
#else
    using namespace boost;
#endif

    int const            shift = T::value;
    unsigned long const  max_u = ULONG_MAX >> shift;
    long const           max_s = LONG_MAX >> shift, min_s = LONG_MIN >> shift;

    BOOST_CHECK_EQUAL( typename uint_value_t<max_u>::least(max_u), max_u );
    BOOST_CHECK_EQUAL( typename uint_value_t<(max_u >> 1)>::least(max_u >> 1),
     max_u >> 1 );
    BOOST_CHECK_EQUAL( typename uint_value_t<max_u>::fast(max_u), max_u );
    BOOST_CHECK_EQUAL( typename uint_value_t<(max_u >> 1)>::fast(max_u >> 1),
     max_u >> 1 );

    BOOST_CHECK_EQUAL( typename int_max_value_t<max_s>::least(max_s), max_s );
    BOOST_CHECK_EQUAL( typename int_max_value_t<(max_s >> 1)>::least(max_s >>
     1), max_s >> 1 );
    BOOST_CHECK_EQUAL( typename int_max_value_t<max_s>::fast(max_s), max_s );
    BOOST_CHECK_EQUAL( typename int_max_value_t<(max_s >> 1)>::fast(max_s >> 1),
     max_s >> 1 );

    BOOST_CHECK_EQUAL( typename int_min_value_t<min_s>::least(min_s), min_s );
    BOOST_CHECK_EQUAL( typename int_min_value_t<(min_s >> 1)>::least(min_s >>
     1), min_s >> 1 );
    BOOST_CHECK_EQUAL( typename int_min_value_t<min_s>::fast(min_s), min_s );
    BOOST_CHECK_EQUAL( typename int_min_value_t<(min_s >> 1)>::fast(min_s >> 1),
     min_s >> 1 );
}

BOOST_AUTO_TEST_SUITE_END()

// Verification of bugs and their fixes
BOOST_AUTO_TEST_SUITE( bug_fix_tests )

BOOST_AUTO_TEST_SUITE_END()
