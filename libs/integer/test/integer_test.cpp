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

#include <boost/test/unit_test.hpp>           // unit testing framework
#include <boost/test/test_case_template.hpp>

#include <boost/config.hpp>          // for BOOST_NO_USING_TEMPLATE, etc.
#include <boost/cstdint.hpp>         // for boost::uintmax_t, intmax_t
#include <boost/integer.hpp>         // for boost::int_t, boost::uint_t, etc.
#include <boost/integer_traits.hpp>  // for boost::integer_traits
#include <boost/limits.hpp>          // for std::numeric_limits

#include <boost/mpl/arithmetic.hpp>      // for boost::mpl::plus, divides
#include <boost/mpl/assert.hpp>          // for BOOST_MPL_ASSERT_RELATION, etc.
#include <boost/mpl/back.hpp>            // for boost::mpl::back
#include <boost/mpl/copy.hpp>            // for boost::mpl::copy
#include <boost/mpl/equal.hpp>           // for boost::mpl::equal
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
#if defined(BOOST_HAS_LONG_LONG) && ((ULLONG_MAX > ULONG_MAX) || (ULONGLONG_MAX > ULONG_MAX))
    , boost::ulong_long_type
#elif defined(BOOST_HAS_MS_INT64) && (0xFFFFFFFFFFFFFFFFui64 > ULONG_MAX)
    , unsigned __int64
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
typedef std::numeric_limits<boost:: intmax_t>   intmax_limits;
typedef std::numeric_limits<boost::uintmax_t>  uintmax_limits;

int const   intmax_bits =  intmax_limits::digits + 1;
int const  uintmax_bits = uintmax_limits::digits;

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
    boost::mpl::integral_c< int, intmax_bits - 3 >
>::type  valid_to_increase_sbits_list;

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
#if defined(BOOST_HAS_LONG_LONG) && ((ULLONG_MAX > ULONG_MAX) || (ULONGLONG_MAX > ULONG_MAX))
    , std::numeric_limits< boost::ulong_long_type >::digits
#elif defined(BOOST_HAS_MS_INT64) && (0xFFFFFFFFFFFFFFFFui64 > ULONG_MAX)
    , std::numeric_limits< unsigned __int64 >::digits
#endif
};

std::size_t const  integral_type_count = sizeof(integral_bit_lengths) /
 sizeof(integral_bit_lengths[0]);

// Use SFINAE to check if a particular bit-count is supported
template < int Bits >
bool
print_out_sized_signed( boost::mpl::integral_c<int, Bits> const &x, int bits,
 typename boost::sized_integral<Bits, signed>::type *unused = 0 )
{
    // Too bad the type-id expression couldn't use the compact form "*unused",
    // but type-ids of dereferenced null pointers throw by order of C++ 2003,
    // sect. 5.2.8, para. 2 (although the result is not conceptually needed).

    PRIVATE_SHOW_MESSAGE( "There is a sized_integral<" << bits <<
     ", signed> specialization, with type '" << typeid(typename
     boost::sized_integral<Bits, signed>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_sized_signed( T const &x, int bits )
{
    PRIVATE_SHOW_MESSAGE( "There is no sized_integral<" << bits <<
     ", signed> specialization." );
    return false;
}

template < int Bits >
bool
print_out_sized_unsigned( boost::mpl::integral_c<int, Bits> const &x, int bits,
 typename boost::sized_integral<Bits, unsigned>::type *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is a sized_integral<" << bits <<
     ", unsigned> specialization, with type '" << typeid(typename
     boost::sized_integral<Bits, unsigned>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_sized_unsigned( T const &x, int bits )
{
    PRIVATE_SHOW_MESSAGE( "There is no sized_integral<" << bits <<
     ", unsigned> specialization." );
    return false;
}

template < int Bits >
bool
print_out_exact_signed( boost::mpl::integral_c<int, Bits> const &x, int bits,
 typename boost::exact_integral<Bits, signed>::type *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is an exact_integral<" << bits <<
     ", signed> specialization, with type '" << typeid(typename
     boost::exact_integral<Bits, signed>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_exact_signed( T const &x, int bits )
{
    PRIVATE_SHOW_MESSAGE( "There is no exact_integral<" << bits <<
     ", signed> specialization." );
    return false;
}

template < int Bits >
bool
print_out_exact_unsigned( boost::mpl::integral_c<int, Bits> const &x, int bits,
 typename boost::exact_integral<Bits, unsigned>::type *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is an exact_integral<" << bits <<
     ", unsigned> specialization, with type '" << typeid(typename
     boost::exact_integral<Bits, unsigned>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_exact_unsigned( T const &x, int bits )
{
    PRIVATE_SHOW_MESSAGE( "There is no exact_integral<" << bits <<
     ", unsigned> specialization." );
    return false;
}

template < boost::intmax_t Value >
bool
print_out_maximum_signed( boost::maximum_signed_integral<Value> const &x,
 boost::intmax_t value, typename boost::maximum_signed_integral<Value>::type
 *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is a maximum_signed_integral<" << value <<
     "> specialization, with type '" << typeid(typename
     boost::maximum_signed_integral<Value>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_maximum_signed( T const &x, boost::intmax_t value )
{
    PRIVATE_SHOW_MESSAGE( "There is no maximum_signed_integral<" << value <<
     "> specialization." );
    return false;
}

template < boost::intmax_t Value >
bool
print_out_minimum_signed( boost::minimum_signed_integral<Value> const &x,
 boost::intmax_t value, typename boost::minimum_signed_integral<Value>::type
 *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is a minimum_signed_integral<" << value <<
     "> specialization, with type '" << typeid(typename
     boost::minimum_signed_integral<Value>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_minimum_signed( T const &x, boost::intmax_t value )
{
    PRIVATE_SHOW_MESSAGE( "There is no minimum_signed_integral<" << value <<
     "> specialization." );
    return false;
}

template < boost::uintmax_t Value >
bool
print_out_maximum_unsigned( boost::maximum_unsigned_integral<Value> const &x,
 boost::uintmax_t value, typename boost::maximum_unsigned_integral<Value>::type
 *unused = 0 )
{
    PRIVATE_SHOW_MESSAGE( "There is a maximum_unsigned_integral<" << value <<
     "> specialization, with type '" << typeid(typename
     boost::maximum_unsigned_integral<Value>::type).name() << "'." );
    return true;
}

template < typename T >
bool
print_out_maximum_unsigned( T const &x, boost::uintmax_t value )
{
    PRIVATE_SHOW_MESSAGE( "There is no maximum_unsigned_integral<" << value <<
     "> specialization." );
    return false;
}

}  // unnamed namespace


// Check the processor-optimzed type system
BOOST_AUTO_TEST_SUITE( optimized_type_tests )

// Check the optimzed type override of a given type
BOOST_AUTO_TEST_CASE( fast_type_test )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using std::numeric_limits;
    using boost::is_same;
#else
    using namespace std;
    using namespace boost;
#endif

    typedef short                               least_type;
    typedef boost::int_fast_t<least_type>::fast  fast_type;
    typedef numeric_limits<least_type>          least_limits;
    typedef numeric_limits<fast_type>            fast_limits;

    typedef boost::fast_integral<least_type>::type  real_fast_type;

    BOOST_MPL_ASSERT_RELATION( (is_same<least_type, fast_type>::value), ==,
     false );
    BOOST_MPL_ASSERT_RELATION( (is_same<fast_type, real_fast_type>::value), ==,
     true );
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
    BOOST_CHECK_EQUAL(   print_out_sized_signed(T(), T::value), T::value <=
      intmax_bits );
    BOOST_CHECK_EQUAL( print_out_sized_unsigned(T(), T::value), T::value <=
     uintmax_bits );
}

// Check the classic specialization type status of given bit lengths, minimum
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_classic_lengths_test, T,
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
    using boost::mpl::equal;
    using boost::maximum_unsigned_integral;
    using boost::sized_integral;
#else
    using namespace boost::mpl;
    using namespace boost;
#endif

    boost::uintmax_t const  one = 1u;
    int const             count = T::value;

    BOOST_MPL_ASSERT( (equal< maximum_unsigned_integral<(one << (count - 2))>,
     sized_integral<count - 1, unsigned> >) );
    BOOST_MPL_ASSERT( (equal< maximum_unsigned_integral<(one << (count - 1))>,
     sized_integral<count, unsigned> >) );
    BOOST_MPL_ASSERT( (equal< maximum_unsigned_integral<(one << count)>,
     sized_integral<count + 1, unsigned> >) );
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
    using boost::mpl::equal;
    using boost::maximum_signed_integral;
    using boost::sized_integral;
    using boost::minimum_signed_integral;
#else
    using namespace boost::mpl;
    using namespace boost;
#endif

    boost::intmax_t const  one = 1;
    int const            count = T::value;

    BOOST_MPL_ASSERT( (equal< maximum_signed_integral<+(one << (count - 2))>,
     sized_integral<count - 1, signed> >) );
    BOOST_MPL_ASSERT( (equal< minimum_signed_integral<-(one << (count - 2))>,
     sized_integral<count - 1, signed> >) );

    BOOST_MPL_ASSERT( (equal< maximum_signed_integral<+(one << (count - 1))>,
     sized_integral<count, signed> >) );
    BOOST_MPL_ASSERT( (equal< minimum_signed_integral<-(one << (count - 1))>,
     sized_integral<count, signed> >) );

    BOOST_MPL_ASSERT( (equal< maximum_signed_integral<+(one << count)>,
     sized_integral<count + 1, signed> >) );
    BOOST_MPL_ASSERT( (equal< minimum_signed_integral<-(one << count)>,
     sized_integral<count + 1, signed> >) );
}

// Check the specialization type status of given bit lengths, exact only
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_exact_lengths_test, T, bits_list )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using std::binary_search;
#else
    using namespace std;
#endif

    BOOST_CHECK_EQUAL(   print_out_exact_signed(T(), T::value),
     binary_search(integral_bit_lengths, integral_bit_lengths +
     integral_type_count, T::value) );
    BOOST_CHECK_EQUAL( print_out_exact_unsigned(T(), T::value),
     binary_search(integral_bit_lengths, integral_bit_lengths +
     integral_type_count, T::value) );
}

// Check the classic specialization type status of given bit lengths, exact only
BOOST_AUTO_TEST_CASE_TEMPLATE( show_types_for_classic_exact_lengths_test, T,
 distinct_integral_bit_counts )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using std::numeric_limits;
    using boost::int_exact_t;
    using boost::uint_exact_t;
#else
    using namespace std;
    using namespace boost;
#endif

    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     int_exact_t<T::value>::exact>::digits, ==, T::value - 1 );
    BOOST_MPL_ASSERT_RELATION( numeric_limits<typename
     uint_exact_t<T::value>::exact>::digits, ==, T::value );
}

// Check if MPL-compatible templates give bad returns for out-of-range values
BOOST_AUTO_TEST_CASE( show_not_type_for_parameter_test )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::sized_integral;
    using boost::mpl::integral_c;
    using boost::exact_integral;
    using boost::maximum_signed_integral;
    using boost::minimum_signed_integral;
    using boost::maximum_unsigned_integral;
#else
    using namespace boost;
    using namespace boost::mpl;
#endif

    typedef sized_integral< 3, signed>   ssz3_type;
    typedef sized_integral< 0, signed>   ssz0_type;
    typedef sized_integral<-3, signed>  ssz3n_type;

    BOOST_CHECK(  print_out_sized_signed(integral_c<int, ssz3_type::bit_count>(),
     ssz3_type::bit_count) );
    BOOST_CHECK( !print_out_sized_signed(integral_c<int, ssz0_type::bit_count>(),
     ssz0_type::bit_count) );
    BOOST_CHECK( !print_out_sized_signed(integral_c<int, ssz3n_type::bit_count>(),
     ssz3n_type::bit_count) );

    typedef sized_integral< 3, unsigned>   usz3_type;
    typedef sized_integral< 0, unsigned>   usz0_type;
    typedef sized_integral<-3, unsigned>  usz3n_type;

    BOOST_CHECK(  print_out_sized_unsigned(integral_c<int, usz3_type::bit_count>(),
     usz3_type::bit_count) );
    BOOST_CHECK(  print_out_sized_unsigned(integral_c<int, usz0_type::bit_count>(),
     usz0_type::bit_count) );
    BOOST_CHECK( !print_out_sized_unsigned(integral_c<int, usz3n_type::bit_count>(),
     usz3n_type::bit_count) );

    typedef exact_integral< 3, signed>   se3_type;
    typedef exact_integral< 0, signed>   se0_type;
    typedef exact_integral<-3, signed>  se3n_type;

    BOOST_CHECK( !print_out_exact_signed(integral_c<int, se3_type::bit_count>(),
     se3_type::bit_count) );
    BOOST_CHECK( !print_out_exact_signed(integral_c<int, se0_type::bit_count>(),
     se0_type::bit_count) );
    BOOST_CHECK( !print_out_exact_signed(integral_c<int, se3n_type::bit_count>(),
     se3n_type::bit_count) );

    typedef exact_integral< 3, unsigned>   ue3_type;
    typedef exact_integral< 0, unsigned>   ue0_type;
    typedef exact_integral<-3, unsigned>  ue3n_type;

    BOOST_CHECK( !print_out_exact_unsigned(integral_c<int, ue3_type::bit_count>(),
     ue3_type::bit_count) );
    BOOST_CHECK( !print_out_exact_unsigned(integral_c<int, ue0_type::bit_count>(),
     ue0_type::bit_count) );
    BOOST_CHECK( !print_out_exact_unsigned(integral_c<int, ue3n_type::bit_count>(),
     ue3n_type::bit_count) );

    typedef maximum_signed_integral< 15>   max15_type;
    typedef maximum_signed_integral<  0>    max0_type;
    typedef maximum_signed_integral<-15>  max15n_type;

    BOOST_CHECK(  print_out_maximum_signed(max15_type(), max15_type::bound) );
    BOOST_CHECK( !print_out_maximum_signed(max0_type(), max0_type::bound) );
    BOOST_CHECK( !print_out_maximum_signed(max15n_type(), max15n_type::bound) );

    typedef minimum_signed_integral< 15>   min15_type;
    typedef minimum_signed_integral<  0>    min0_type;
    typedef minimum_signed_integral<-15>  min15n_type;

    BOOST_CHECK( !print_out_minimum_signed(min15_type(), min15_type::bound) );
    BOOST_CHECK( !print_out_minimum_signed(min0_type(), min0_type::bound) );
    BOOST_CHECK(  print_out_minimum_signed(min15n_type(), min15n_type::bound) );

    typedef maximum_unsigned_integral<15>   umax15_type;
    typedef maximum_unsigned_integral< 0>    umax0_type;

    BOOST_CHECK( print_out_maximum_unsigned(umax15_type(), umax15_type::bound) );
    BOOST_CHECK( print_out_maximum_unsigned(umax0_type(), umax0_type::bound) );
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
    //      Template:Max = { intmax_t.Max for int_t, uintmax_t.Max for uint_t }
    // In other words, the selected type doesn't mask out any bits it's not
    // supposed to.  But now we'll use template meta-programming instead of
    // macros.  The limit of type-lists is usually less than 32 (not to mention
    // 64) elements, so we have to take selected values.
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::sized_integral;
    using boost::uint_t;
    using boost::int_t;
#else
    using namespace boost;
#endif

    int const                 count = T::value, shift = uintmax_bits - count;
    boost::uintmax_t const  value_u = uintmax_limits::max
     BOOST_PREVENT_MACRO_SUBSTITUTION () >> shift;
    boost::intmax_t const   value_s = intmax_limits::max
     BOOST_PREVENT_MACRO_SUBSTITUTION () >> shift;

    BOOST_CHECK_EQUAL( (typename sized_integral<count, unsigned>::type(value_u)),
     value_u );
    BOOST_CHECK_EQUAL( typename uint_t<count - 1>::least(value_u >> 1), value_u
     >> 1 );
    BOOST_CHECK_EQUAL( typename uint_t<count>::fast(value_u), value_u );
    BOOST_CHECK_EQUAL( typename uint_t<count - 1>::fast(value_u >> 1), value_u
     >> 1 );

    BOOST_CHECK_EQUAL( typename int_t<count>::least(value_s), value_s );
    BOOST_CHECK_EQUAL( (typename sized_integral<count - 1, signed>::type(value_s
     >> 1)), value_s >> 1 );
    BOOST_CHECK_EQUAL( typename int_t<count>::fast(value_s), value_s );
    BOOST_CHECK_EQUAL( typename int_t<count - 1>::fast(value_s >> 1), value_s >>
     1 );
}

// Check if a large value can only fit of its exact bit length
BOOST_AUTO_TEST_CASE_TEMPLATE( fit_for_exact_lengths_test, T,
 distinct_integral_bit_counts )
{
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::exact_integral;
#else
    using namespace boost;
#endif

    typedef typename exact_integral<T::value, unsigned>::type  uexact_type;
    typedef typename exact_integral<T::value,   signed>::type  sexact_type;

    uexact_type const  one_u( 1u ), high_bit_u( one_u << (T::value - 1) ),
                       repeated_bits_u( (high_bit_u << 1) | high_bit_u );

    BOOST_CHECK( high_bit_u );
    BOOST_CHECK_EQUAL( repeated_bits_u, high_bit_u );

    sexact_type const  one_s( 1 ), high_bit_s( one_s << (T::value - 2) ),
                       repeated_bits_s( (high_bit_s << 1) | high_bit_s ),
                       repeated_2bits_s( (repeated_bits_s << 1) | high_bit_s );

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
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::uint_value_t;
#else
    using namespace boost;
#endif

    uintmax_t const  max_u = boost::integer_traits<uintmax_t>::const_max >>
     T::value;

    BOOST_CHECK_EQUAL( typename uint_value_t<max_u>::least(max_u), max_u );
    BOOST_CHECK_EQUAL( typename uint_value_t<(max_u >> 1)>::least(max_u >> 1),
     max_u >> 1 );
    BOOST_CHECK_EQUAL( typename uint_value_t<max_u>::fast(max_u), max_u );
    BOOST_CHECK_EQUAL( typename uint_value_t<(max_u >> 1)>::fast(max_u >> 1),
     max_u >> 1 );
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
#ifndef BOOST_NO_USING_TEMPLATE
    using boost::integer_traits;
    using boost::int_max_value_t;
    using boost::int_min_value_t;
#else
    using namespace boost;
#endif

    int const       shift = T::value;
    intmax_t const  max_s = integer_traits<intmax_t>::const_max >> shift,
                    min_s = integer_traits<intmax_t>::const_min >> shift;

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
