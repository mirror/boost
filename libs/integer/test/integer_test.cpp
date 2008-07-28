//  boost integer.hpp test program  ------------------------------------------//

//  Copyright Beman Dawes 1999.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/integer for documentation.

//  Revision History
//   16 Jul 08  Added MPL-compatible variants of the minimum-size and value-
//              based integer templates. (Daryle Walker)
//   15 Jul 08  Added exact-integer templates; added MPL-compatible variant of
//              processor-optimized integer template. (Daryle Walker)
//   14 Jul 08  Improved testing of processor-optimized integer template; added
//              extended-integer support. (Daryle Walker)
//   13 Jul 08  Modernized tests w/ MPL instead of giant macros (Daryle Walker)
//   07 Jul 08  Changed tests to use the unit-test system (Daryle Walker)
//   04 Oct 01  Added tests for new templates; rewrote code (Daryle Walker)
//   10 Mar 01  Boost Test Library now used for tests (Beman Dawes)
//   31 Aug 99  Initial version

#define BOOST_TEST_MODULE  "Integer size-selection tests"

#include <boost/test/unit_test.hpp>  // unit testing framework

#include <boost/config.hpp>          // for BOOST_NO_SFINAE
#include <boost/cstdint.hpp>         // for boost::uintmax_t, intmax_t
#include <boost/integer.hpp>         // for boost::int_t, boost::uint_t, etc.
#include <boost/integer_traits.hpp>  // for boost::integer_traits
#include <boost/limits.hpp>          // for std::numeric_limits

#include <boost/detail/extended_integer.hpp>  // BOOST_HAS_XINT, BOOST_UXINT_MAX

#include <boost/mpl/arithmetic.hpp>      // for boost::mpl::plus, divides
#include <boost/mpl/assert.hpp>          // for BOOST_MPL_ASSERT_RELATION, etc.
#include <boost/mpl/back.hpp>            // for boost::mpl::back
#include <boost/mpl/copy.hpp>            // for boost::mpl::copy
#include <boost/mpl/equal.hpp>           // for boost::mpl::equal
#include <boost/mpl/front_inserter.hpp>  // for boost::mpl::front_inserter
#include <boost/mpl/int.hpp>             // for boost::mpl::int_
#include <boost/mpl/integral_c.hpp>      // for boost::mpl::integral_c
#include <boost/mpl/joint_view.hpp>      // for boost::mpl::joint_view
#include <boost/mpl/pop_back.hpp>        // for boost::mpl::pop_back
#include <boost/mpl/push_back.hpp>       // for boost::mpl::push_back 
#include <boost/mpl/push_front.hpp>      // for boost::mpl::push_front
#include <boost/mpl/range_c.hpp>         // for boost::mpl::range_c
#include <boost/mpl/shift_right.hpp>     // for boost::mpl::shift_right
#include <boost/mpl/sort.hpp>            // for boost::mpl::sort
#include <boost/mpl/transform.hpp>       // for boost::mpl::transform
#include <boost/mpl/transform_view.hpp>  // for boost::mpl::transform_view
#include <boost/mpl/unpack_args.hpp>     // for boost::mpl::unpack_args
#include <boost/mpl/vector.hpp>          // for boost::mpl::vector
#include <boost/mpl/zip_view.hpp>        // for boost::mpl::zip_view

#include <boost/type_traits/is_same.hpp>      // for boost::is_same
#include <boost/type_traits/make_signed.hpp>  // for boost::make_signed

#include <algorithm>  // for std::binary_search
#include <climits>    // for ULONG_MAX, LONG_MAX, LONG_MIN, etc.
#include <cstddef>    // for std::size_t
#include <iostream>   // for std::cout
#include <ostream>    // for std::endl
#include <typeinfo>   // for std::type_info


// Control what the "fast" specialization of "short" is
#ifndef CONTROL_FAST_SHORT
#define CONTROL_FAST_SHORT  long
#endif

// Control if the names of the types for each version
// of the integer templates will be printed.
#ifndef CONTROL_SHOW_TYPES
#define CONTROL_SHOW_TYPES  0
#endif

// Control if every potential bit-count is used, or only a selection
// For me, full counts increase compile time from 90 seconds to 20 minutes!
#ifndef CONTROL_FULL_COUNTS
#define CONTROL_FULL_COUNTS  1
#endif


// If specializations have not already been done, then we can confirm
// the effects of the fast types by making a specialization.  If there
// is a specialization for "short," make sure that CONTROL_FAST_SHORT
// is set to a type distinct from "short" and the default implementation.
namespace boost
{
    template < >
    struct fast_integral< short >
    {
        typedef CONTROL_FAST_SHORT  type;
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
#if BOOST_HAS_XINT && (BOOST_UXINT_MAX > ULONG_MAX)
    , boost::detail::uxint_t
#endif
>  distinct_unsigned_types;

typedef boost::mpl::transform<
    distinct_unsigned_types,
    boost::make_signed< boost::mpl::_1 >
>::type  distinct_signed_types;

// List the digit counts for each integral type
template < typename T >
struct digits_of
    : boost::mpl::int_< std::numeric_limits<T>::digits >
{
};

typedef boost::mpl::transform<
    distinct_unsigned_types,
    digits_of< boost::mpl::_1 >
>::type  distinct_integral_bit_counts;

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
typedef std::numeric_limits<boost:: intmax_t>   intmax_limits;
typedef std::numeric_limits<boost::uintmax_t>  uintmax_limits;

int const   intmax_bits =  intmax_limits::digits + 1;
int const  uintmax_bits = uintmax_limits::digits;

// Make master lists including an outlier beyond all valid bit counts
#if CONTROL_FULL_COUNTS
typedef boost::mpl::range_c<int, 0, uintmax_bits + 2>  bits_list;
#else
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
#endif

// Remove the outlier when all bits counts must be valid
#if CONTROL_FULL_COUNTS
typedef boost::mpl::range_c<int, 0, uintmax_bits + 1>  valid_bits_list;
#else
typedef boost::mpl::pop_back<bits_list>::type  valid_bits_list;
#endif

// Replace the minimum bit count with one more, so right-shifting by a stored
// value doesn't give an invalid result
#if CONTROL_FULL_COUNTS
typedef boost::mpl::range_c<int, 1, uintmax_bits + 1>
  valid_to_decrease_bits_list;
#else
typedef valid_bits_list  valid_to_decrease_bits_list;
#endif

// Replace the maximum bit count with one less, so left-shifting by a stored
// value doesn't give an invalid result
#if CONTROL_FULL_COUNTS
typedef boost::mpl::range_c<int, 0, uintmax_bits>  valid_to_increase_ubits_list;
#else
typedef boost::mpl::push_back<
    boost::mpl::pop_back< valid_bits_list >::type,
    boost::mpl::integral_c< int, uintmax_bits - 1 >
>::type  valid_to_increase_ubits_list;
#endif

// Do it again for signed types since they have one-less bit to use for the
// mantissa (don't want to shift into the sign bit)
#if CONTROL_FULL_COUNTS
typedef boost::mpl::range_c<int, 0, intmax_bits - 2>
  valid_to_increase_sbits_list;
#else
typedef boost::mpl::push_back<
    boost::mpl::pop_back< valid_bits_list >::type,
    boost::mpl::integral_c< int, intmax_bits - 3 >
>::type  valid_to_increase_sbits_list;
#endif

// List the digit counts for each integral type, this time as an object, an
// array working as a sorted list
int const  integral_bit_lengths[] = {
    std::numeric_limits< unsigned char >::digits
#if USHRT_MAX > UCHAR_MAX
    , std::numeric_limits< unsigned short >::digits
#endif
#if UINT_MAX > USHRT_MAX
    , std::numeric_limits< unsigned int >::digits
#endif
#if ULONG_MAX > UINT_MAX
    , std::numeric_limits< unsigned long >::digits
#endif
#if BOOST_HAS_XINT && (BOOST_UXINT_MAX > ULONG_MAX)
    , std::numeric_limits< boost::detail::uxint_t >::digits
#endif
};

std::size_t const  integral_type_count = sizeof(integral_bit_lengths) /
 sizeof(integral_bit_lengths[0]);

// "Template-typedefs" to reduce two-argument templates to single-argument.
// This way, all the MPL-compatible templates have the same form, for below.
template < int Bits >
struct signed_sized_integral  : boost::sized_integral<Bits, signed>  {};

template < int Bits >
struct unsigned_sized_integral  : boost::sized_integral<Bits, unsigned>  {};

template < int Bits >
struct signed_exact_integral  : boost::exact_integral<Bits, signed>  {};

template < int Bits >
struct unsigned_exact_integral  : boost::exact_integral<Bits, unsigned>  {};

// Use SFINAE to check if a particular parameter is supported
#ifndef BOOST_NO_SFINAE
template < typename ValueT, template<ValueT> class Tmpl, ValueT Value >
bool
print_out_template( Tmpl<Value> const &, ValueT setting, char const
 *template_pre_name, char const *template_post_name, typename Tmpl<Value>::type
 *unused = 0 )
{
    // Too bad the type-id expression couldn't use the compact form "*unused",
    // but type-ids of dereferenced null pointers throw by order of C++ 2003,
    // sect. 5.2.8, para. 2 (although the result is not conceptually needed).
    PRIVATE_SHOW_MESSAGE( "This is " << template_pre_name << setting
     << template_post_name << " specialization, with type '" << typeid(typename
     Tmpl<Value>::type).name() << "'." );
    return true;
}

template < typename ValueT, typename T >
bool
print_out_template( T const &, ValueT setting, char const *template_pre_name,
 char const *template_post_name )
{
    PRIVATE_SHOW_MESSAGE( "Looking for " << template_pre_name << setting
     << template_post_name << " specialization?  It doesn't exist." );
    return false;
}
#else
#error "These tests cannot work without Substitution-Failure-Is-Not-An-Error"
#endif

// Get the extreme values for each integral type
template < typename T >
struct minimum_of
    : boost::mpl::integral_c< T, boost::integer_traits<T>::const_min >
{
};

template < typename T >
struct maximum_of
    : boost::mpl::integral_c< T, boost::integer_traits<T>::const_max >
{
};

}  // unnamed namespace


// Check the processor-optimzed type system
BOOST_AUTO_TEST_SUITE( optimized_type_tests )

// Check the optimzed type override of a given type
BOOST_AUTO_TEST_CASE( fast_type_test )
{
    typedef short                               least_type;
    typedef boost::int_fast_t<least_type>::fast  fast_type;
    typedef std::numeric_limits<least_type>     least_limits;
    typedef std::numeric_limits<fast_type>       fast_limits;

    typedef boost::fast_integral<least_type>::type  real_fast_type;

    BOOST_MPL_ASSERT_RELATION( (boost::is_same<least_type, fast_type>::value),
     ==, false );
    BOOST_MPL_ASSERT_RELATION( (boost::is_same<fast_type,
     real_fast_type>::value), ==, true );
    BOOST_MPL_ASSERT_RELATION( fast_limits::is_specialized, ==, true );
    BOOST_MPL_ASSERT_RELATION( fast_limits::is_signed &&
     fast_limits::is_bounded, ==, true );
    BOOST_MPL_ASSERT_RELATION( fast_limits::radix, ==, 2 );
    BOOST_MPL_ASSERT_RELATION( fast_limits::digits, >=, least_limits::digits );
}

BOOST_AUTO_TEST_SUITE_END()

// Check if given types can support given size parameters
BOOST_AUTO_TEST_SUITE( show_type_tests )

// Check the specialization type status of given bit lengths, minimum
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_lengths_test, T, bits_list )
{
    BOOST_CHECK_EQUAL( print_out_template(signed_sized_integral<T::value>(),
     T::value, "a sized_integral<", ", signed>"), T::value && (T::value <=
     intmax_bits) );
    BOOST_CHECK_EQUAL( print_out_template(unsigned_sized_integral<T::value>(),
     T::value, "a sized_integral<", ", unsigned>"), T::value <= uintmax_bits );
}

// Check the classic specialization type status of given bit lengths, minimum,
// unsigned
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_classic_lengths_unsigned_test, T,
 valid_bits_list )
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
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::uint_t<T::value>::least>::digits, >=, T::value );
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::uint_t<T::value>::fast>::digits, >=, T::value );
}

// Check the classic specialization type status of given bit lengths, minimum,
// signed
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_classic_lengths_signed_test, T,
 valid_to_decrease_bits_list )
{
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::int_t<T::value>::least>::digits, >=, T::value - 1 );
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::int_t<T::value>::fast>::digits, >=, T::value - 1 );
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
    boost::uintmax_t const  one = 1u;

    BOOST_MPL_ASSERT( (boost::mpl::equal< boost::maximum_unsigned_integral<(one
     << T::value)>, unsigned_sized_integral<T::value + 1> >) );
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
    static  boost::intmax_t const  one = 1;

    BOOST_MPL_ASSERT( (boost::mpl::equal< boost::maximum_signed_integral<+(one
     << T::value)>, signed_sized_integral<T::value + 1> >) );
    BOOST_MPL_ASSERT( (boost::mpl::equal< boost::minimum_signed_integral<-(one
     << T::value)>, signed_sized_integral<T::value + 1> >) );
}

// Check the specialization type status of given bit lengths, exact only
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_exact_lengths_test, T, bits_list )
{
    bool const  is_exact_length = std::binary_search( integral_bit_lengths,
     integral_bit_lengths + integral_type_count, T::value );

    BOOST_CHECK_EQUAL( print_out_template(signed_exact_integral<T::value>(),
     T::value, "an exact_integral<", ", signed>"), is_exact_length );
    BOOST_CHECK_EQUAL( print_out_template(unsigned_exact_integral<T::value>(),
     T::value, "an exact_integral<", ", unsigned>"), is_exact_length );
}

// Check the classic specialization type status of given bit lengths, exact only
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_classic_exact_lengths_test, T,
 distinct_integral_bit_counts )
{
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::int_exact_t<T::value>::exact>::digits, ==, T::value - 1 );
    BOOST_MPL_ASSERT_RELATION( std::numeric_limits<typename
     boost::uint_exact_t<T::value>::exact>::digits, ==, T::value );
}

// Check if MPL-compatible templates give bad returns for out-of-range values
BOOST_AUTO_TEST_CASE( show_not_type_for_parameter_test )
{
    typedef signed_sized_integral< 3>   ssz3_type;
    typedef signed_sized_integral< 0>   ssz0_type;
    typedef signed_sized_integral<-3>  ssz3n_type;

    BOOST_CHECK(  print_out_template(ssz3_type(), ssz3_type::bit_count,
     "a sized_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(ssz0_type(), ssz0_type::bit_count,
     "a sized_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(ssz3n_type(), ssz3n_type::bit_count,
     "a sized_integral<", ", signed>") );

    typedef unsigned_sized_integral< 3>   usz3_type;
    typedef unsigned_sized_integral< 0>   usz0_type;
    typedef unsigned_sized_integral<-3>  usz3n_type;

    BOOST_CHECK(  print_out_template(usz3_type(), usz3_type::bit_count,
     "a sized_integral<", ", unsigned>") );
    BOOST_CHECK(  print_out_template(usz0_type(), usz0_type::bit_count,
     "a sized_integral<", ", unsigned>") );
    BOOST_CHECK( !print_out_template(usz3n_type(), usz3n_type::bit_count,
     "a sized_integral<", ", unsigned>") );

    typedef signed_exact_integral< CHAR_BIT >     se8_type;
    typedef signed_exact_integral< 3>             se3_type;
    typedef signed_exact_integral< 0>             se0_type;
    typedef signed_exact_integral<-3>            se3n_type;
    typedef signed_exact_integral< - CHAR_BIT >  se8n_type;

    BOOST_CHECK(  print_out_template(se8_type(), se8_type::bit_count,
     "an exact_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(se3_type(), se3_type::bit_count,
     "an exact_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(se0_type(), se0_type::bit_count,
     "an exact_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(se3n_type(), se3n_type::bit_count,
     "an exact_integral<", ", signed>") );
    BOOST_CHECK( !print_out_template(se8n_type(), se8n_type::bit_count,
     "an exact_integral<", ", signed>") );

    typedef unsigned_exact_integral< CHAR_BIT >     ue8_type;
    typedef unsigned_exact_integral< 3>             ue3_type;
    typedef unsigned_exact_integral< 0>             ue0_type;
    typedef unsigned_exact_integral<-3>            ue3n_type;
    typedef unsigned_exact_integral< - CHAR_BIT >  ue8n_type;

    BOOST_CHECK(  print_out_template(ue8_type(), ue8_type::bit_count,
     "an exact_integral<", ", unsigned>") );
    BOOST_CHECK( !print_out_template(ue3_type(), ue3_type::bit_count,
     "an exact_integral<", ", unsigned>") );
    BOOST_CHECK( !print_out_template(ue0_type(), ue0_type::bit_count,
     "an exact_integral<", ", unsigned>") );
    BOOST_CHECK( !print_out_template(ue3n_type(), ue3n_type::bit_count,
     "an exact_integral<", ", unsigned>") );
    BOOST_CHECK( !print_out_template(ue8n_type(), ue8n_type::bit_count,
     "an exact_integral<", ", unsigned>") );

    typedef boost::maximum_signed_integral< 15>   max15_type;
    typedef boost::maximum_signed_integral<  0>    max0_type;
    typedef boost::maximum_signed_integral<-15>  max15n_type;

    BOOST_CHECK(  print_out_template(max15_type(), max15_type::bound,
     "a maximum_signed_integral<", ">") );
    BOOST_CHECK( !print_out_template(max0_type(), max0_type::bound,
     "a maximum_signed_integral<", ">") );
    BOOST_CHECK( !print_out_template(max15n_type(), max15n_type::bound,
     "a maximum_signed_integral<", ">") );

    typedef boost::minimum_signed_integral< 15>   min15_type;
    typedef boost::minimum_signed_integral<  0>    min0_type;
    typedef boost::minimum_signed_integral<-15>  min15n_type;

    BOOST_CHECK( !print_out_template(min15_type(), min15_type::bound,
     "a minimum_signed_integral<", ">") );
    BOOST_CHECK( !print_out_template(min0_type(), min0_type::bound,
     "a minimum_signed_integral<", ">") );
    BOOST_CHECK(  print_out_template(min15n_type(), min15n_type::bound,
     "a minimum_signed_integral<", ">") );

    typedef boost::maximum_unsigned_integral<15>   umax15_type;
    typedef boost::maximum_unsigned_integral< 0>    umax0_type;

    BOOST_CHECK( print_out_template(umax15_type(), umax15_type::bound,
     "a maximum_unsigned_integral<", ">") );
    BOOST_CHECK( print_out_template(umax0_type(), umax0_type::bound,
     "a maximum_unsigned_integral<", ">") );
}

BOOST_AUTO_TEST_SUITE_END()

// Check if given constants can fit in given types
BOOST_AUTO_TEST_SUITE( fit_type_tests )

// Check if large value can fit its minimum required size, by size
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_masked_values_test, T,
 valid_to_decrease_bits_list )
{
    // This test is supposed to replace the following checks given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for ( N = 32, V = Template:Max ; N >= 0 ; --N, V >>= 1 )
    //      Confirm( static_cast<typename Template<N>::Type>(V) == V );
    //  end for
    // end Routine
    // with Template = {int_t, uint_t}; Type = {least, fast};
    //      Template:Max = { intmax_t.Max for int_t, uintmax_t.Max for uint_t }
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
    static  int const       count = T::value;
    int const               shift = uintmax_bits - count;
    boost::uintmax_t const  value_u = uintmax_limits::max
     BOOST_PREVENT_MACRO_SUBSTITUTION () >> shift;
    boost::intmax_t const   value_s = intmax_limits::max
     BOOST_PREVENT_MACRO_SUBSTITUTION () >> shift;

    BOOST_CHECK_EQUAL( static_cast<typename
     unsigned_sized_integral<count>::type>(value_u), value_u );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::uint_t<count>::least>(value_u), value_u );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::uint_t<count>::fast>(value_u), value_u );

    BOOST_CHECK_EQUAL( static_cast<typename
     signed_sized_integral<count>::type>(value_s), value_s );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_t<count>::least>(value_s), value_s );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_t<count>::fast>(value_s), value_s );
}

// Check if a large value can only fit of its exact bit length
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_exact_lengths_test, T,
 distinct_integral_bit_counts )
{
    typename boost::exact_integral<T::value, unsigned>::type const  one_u( 1u ),
     high_bit_u( one_u << (T::value - 1) ), repeated_bits_u( (high_bit_u << 1) |
     high_bit_u );

    BOOST_CHECK( high_bit_u );
    BOOST_CHECK_EQUAL( repeated_bits_u, high_bit_u );

    typename boost::exact_integral<T::value, signed>::type const  one_s( 1 ),
     high_bit_s( one_s << (T::value - 2) ), repeated_bits_s( (high_bit_s << 1) |
     high_bit_s ), repeated_2bits_s( (repeated_bits_s << 1) | high_bit_s );

    BOOST_CHECK( high_bit_s > 0 );
    BOOST_CHECK( repeated_bits_s < 0 );
    BOOST_CHECK_EQUAL( repeated_bits_s, repeated_2bits_s );
}

// Check if large value can fit its minimum required size, by value, unsigned
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_shifted_unsigned_values_test, T,
 valid_to_increase_ubits_list )
{
    // This test is supposed to replace the following checks given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for ( N = 0, V = Template:Extreme ; N < 32 ; ++N, V >>= 1 )
    //      Confirm( static_cast<typename Template<V>::Type>(V) == V );
    //  end for
    // end Routine
    // with Template = {uint_value_t}; Type = {least, fast}; Template:Extreme =
    //      {uintmax_t.Max for uint_value_t}
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
    using boost::uintmax_t;

    typedef boost::mpl::shift_right<maximum_of<uintmax_t>, T>  maxi_type;

    uintmax_t const  maxi = maxi_type::value;

    BOOST_CHECK_EQUAL( static_cast<typename
     boost::uint_value_t<maxi_type::value>::least>(maxi), maxi );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::uint_value_t<maxi_type::value>::fast>(maxi), maxi );
}

// Check if large value can fit its minimum required size, by value, signed
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_shifted_signed_values_test, T,
 valid_to_increase_sbits_list )
{
    // This test is supposed to replace the following checks given in
    // puesdo-code by:
    // Routine: Template, Type
    //  for ( N = 0, V = Template:Extreme ; N < 32 ; ++N, V >>= 1 )
    //      Confirm( static_cast<typename Template<V>::Type>(V) == V );
    //  end for
    // end Routine
    // with Template = {int_max_value_t, int_min_value_t}; Type = {least, fast};
    //      Template:Extreme = {intmax_t.Min for int_min_value_t, intmax_t.Max
    //      for int_max_value_t}
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
    using boost::intmax_t;

    typedef boost::mpl::shift_right<minimum_of<intmax_t>, T>  mini_type;
    typedef boost::mpl::shift_right<maximum_of<intmax_t>, T>  maxi_type;

    intmax_t const  maxi = maxi_type::value, mini = mini_type::value;

    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_max_value_t<maxi_type::value>::least>(maxi), maxi );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_max_value_t<maxi_type::value>::fast>(maxi), maxi );

    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_min_value_t<mini_type::value>::least>(mini), mini );
    BOOST_CHECK_EQUAL( static_cast<typename
     boost::int_min_value_t<mini_type::value>::fast>(mini), mini );
}

BOOST_AUTO_TEST_SUITE_END()

// Verification of bugs and their fixes
BOOST_AUTO_TEST_SUITE( bug_fix_tests )

BOOST_AUTO_TEST_SUITE_END()
