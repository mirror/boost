/*
 *  A test program for boost/rational.hpp.
 *  Change the typedef at the beginning of run_tests() to try out different
 *  integer types.  (These tests are designed only for signed integer
 *  types.  They should work for short, int and long.)
 *
 *  (C) Copyright Stephen Silver, 2001. Permission to copy, use, modify, sell
 *  and distribute this software is granted provided this copyright notice
 *  appears in all copies. This software is provided "as is" without express or
 *  implied warranty, and with no claim as to its suitability for any purpose.
 *
 *  Incorporated into the boost rational number library, and modified and
 *  extended, by Paul Moore, with permission.
 */

// Revision History
// 18 Oct 06  Various fixes for old compilers (Joaquín M López Muñoz)
// 27 Dec 05  Add testing for Boolean conversion operator (Daryle Walker)
// 24 Dec 05  Change code to use Boost.Test (Daryle Walker)
// 04 Mar 01  Patches for Intel C++ and GCC (David Abrahams)

#define BOOST_TEST_MAIN  "Boost::Rational unit tests"

#include <boost/mpl/list.hpp>
#include <boost/operators.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/rational.hpp>

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/test/test_case_template.hpp>

#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

// We can override this on the compile, as -DINT_TYPE=short or whatever.
// The default test is against rational<long>.
#ifndef INT_TYPE
#define INT_TYPE long
#endif

namespace {

// This is a trivial user-defined wrapper around the built in int type.
// It can be used as a test type for rational<>
class MyInt : boost::operators<MyInt>
{
    int val;
public:
    MyInt(int n = 0) : val(n) {}
    friend MyInt operator+ (const MyInt&);
    friend MyInt operator- (const MyInt&);
    MyInt& operator+= (const MyInt& rhs) { val += rhs.val; return *this; }
    MyInt& operator-= (const MyInt& rhs) { val -= rhs.val; return *this; }
    MyInt& operator*= (const MyInt& rhs) { val *= rhs.val; return *this; }
    MyInt& operator/= (const MyInt& rhs) { val /= rhs.val; return *this; }
    MyInt& operator%= (const MyInt& rhs) { val %= rhs.val; return *this; }
    MyInt& operator|= (const MyInt& rhs) { val |= rhs.val; return *this; }
    MyInt& operator&= (const MyInt& rhs) { val &= rhs.val; return *this; }
    MyInt& operator^= (const MyInt& rhs) { val ^= rhs.val; return *this; }
    const MyInt& operator++() { ++val; return *this; }
    const MyInt& operator--() { --val; return *this; }
    bool operator< (const MyInt& rhs) const { return val < rhs.val; }
    bool operator== (const MyInt& rhs) const { return val == rhs.val; }
    bool operator! () const { return !val; }
    friend std::istream& operator>>(std::istream&, MyInt&);
    friend std::ostream& operator<<(std::ostream&, const MyInt&);
};

inline MyInt operator+(const MyInt& rhs) { return rhs; }
inline MyInt operator-(const MyInt& rhs) { return MyInt(-rhs.val); }
inline std::istream& operator>>(std::istream& is, MyInt& i) { is >> i.val; return is; }
inline std::ostream& operator<<(std::ostream& os, const MyInt& i) { os << i.val; return os; }
inline MyInt abs(MyInt rhs) { if (rhs < MyInt()) rhs = -rhs; return rhs; }

// This fixture replaces the check of rational's packing at the start of main.
class rational_size_check
{
    typedef INT_TYPE                          int_type;
    typedef ::boost::rational<int_type>  rational_type;

public:
    rational_size_check()
    {
        using ::std::cout;

        char const * const  int_name = BOOST_PP_STRINGIZE( INT_TYPE );

        cout << "Running tests for boost::rational<" << int_name << ">\n\n";

        cout << "Implementation issue: the minimal size for a rational\n"
             << "is twice the size of the underlying integer type.\n\n";

        cout << "Checking to see if space is being wasted.\n"
             << "\tsizeof(" << int_name << ") == " << sizeof( int_type )
             << "\n";
        cout <<  "\tsizeof(boost::rational<" << int_name << ">) == "
             << sizeof( rational_type ) << "\n\n";

        cout << "Implementation has "
             << ( 
                  (sizeof( rational_type ) > 2u * sizeof( int_type ))
                  ? "included padding bytes"
                  : "minimal size"
                )
             << "\n\n";
    }
};

// This fixture groups all the common settings.
class my_configuration
{
public:
    template < typename T >
    class hook
    {
    public:
        typedef ::boost::rational<T>  rational_type;

    private:
        struct parts { rational_type parts_[ 9 ]; };

        static  parts  generate_rationals()
        {
            rational_type  r1, r2( 0 ), r3( 1 ), r4( -3 ), r5( 7, 2 ),
                           r6( 5, 15 ), r7( 14, -21 ), r8( -4, 6 ),
                           r9( -14, -70 );
            parts result;
            result.parts_[0] = r1;
            result.parts_[1] = r2;
            result.parts_[2] = r3;
            result.parts_[3] = r4;
            result.parts_[4] = r5;
            result.parts_[5] = r6;
            result.parts_[6] = r7;
            result.parts_[7] = r8;
            result.parts_[8] = r9;

            return result;
        }

        parts  p_;  // Order Dependency

    public:
        rational_type  ( &r_ )[ 9 ];  // Order Dependency

        hook() : p_( generate_rationals() ), r_( p_.parts_ ) {}
    };
};

// Instead of controlling the integer type needed with a #define, use a list of
// all available types.  Since the headers #included don't change because of the
// integer #define, only the built-in types and MyInt are available.  (Any other
// arbitrary integer type introduced by the #define would get compiler errors
// because its header can't be #included.)
typedef ::boost::mpl::list<short, int, long>     builtin_signed_test_types;
typedef ::boost::mpl::list<short, int, long, MyInt>  all_signed_test_types;

// Without these explicit instantiations, MSVC++ 6.5/7.0 does not find
// some friend operators in certain contexts.
::boost::rational<short> dummy1;
::boost::rational<int>   dummy2;
::boost::rational<long>  dummy3;
::boost::rational<MyInt> dummy4;

// Should there be tests with unsigned integer types?

} // namespace


// Check if rational is the smallest size possible
BOOST_GLOBAL_FIXTURE( rational_size_check )


// The factoring function template suite
BOOST_AUTO_TEST_SUITE( factoring_suite )

// GCD tests
BOOST_AUTO_TEST_CASE_TEMPLATE( gcd_test, T, all_signed_test_types )
{
    BOOST_CHECK_EQUAL( boost::gcd<T>(  1,  -1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::gcd<T>( -1,   1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  1,   1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::gcd<T>( -1,  -1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  0,   0), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  7,   0), static_cast<T>( 7) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  0,   9), static_cast<T>( 9) );
    BOOST_CHECK_EQUAL( boost::gcd<T>( -7,   0), static_cast<T>( 7) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  0,  -9), static_cast<T>( 9) );
    BOOST_CHECK_EQUAL( boost::gcd<T>( 42,  30), static_cast<T>( 6) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(  6,  -9), static_cast<T>( 3) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(-10, -10), static_cast<T>(10) );
    BOOST_CHECK_EQUAL( boost::gcd<T>(-25, -10), static_cast<T>( 5) );
}

// LCM tests
BOOST_AUTO_TEST_CASE_TEMPLATE( lcm_test, T, all_signed_test_types )
{
    BOOST_CHECK_EQUAL( boost::lcm<T>(  1,  -1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( -1,   1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(  1,   1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( -1,  -1), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(  0,   0), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(  6,   0), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(  0,   7), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( -5,   0), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(  0,  -4), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( 18,  30), static_cast<T>(90) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( -6,   9), static_cast<T>(18) );
    BOOST_CHECK_EQUAL( boost::lcm<T>(-10, -10), static_cast<T>(10) );
    BOOST_CHECK_EQUAL( boost::lcm<T>( 25, -10), static_cast<T>(50) );
}

BOOST_AUTO_TEST_SUITE_END()


// The basic test suite
BOOST_FIXTURE_TEST_SUITE( basic_rational_suite, my_configuration )

// Initialization tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_initialization_test, T,
 all_signed_test_types )
{
    my_configuration::hook<T>  h;
    boost::rational<T>  &r1 = h.r_[ 0 ], &r2 = h.r_[ 1 ], &r3 = h.r_[ 2 ],
                        &r4 = h.r_[ 3 ], &r5 = h.r_[ 4 ], &r6 = h.r_[ 5 ],
                        &r7 = h.r_[ 6 ], &r8 = h.r_[ 7 ], &r9 = h.r_[ 8 ];

    BOOST_CHECK_EQUAL( r1.numerator(), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( r2.numerator(), static_cast<T>( 0) );
    BOOST_CHECK_EQUAL( r3.numerator(), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( r4.numerator(), static_cast<T>(-3) );
    BOOST_CHECK_EQUAL( r5.numerator(), static_cast<T>( 7) );
    BOOST_CHECK_EQUAL( r6.numerator(), static_cast<T>( 1) );
    BOOST_CHECK_EQUAL( r7.numerator(), static_cast<T>(-2) );
    BOOST_CHECK_EQUAL( r8.numerator(), static_cast<T>(-2) );
    BOOST_CHECK_EQUAL( r9.numerator(), static_cast<T>( 1) );

    BOOST_CHECK_EQUAL( r1.denominator(), static_cast<T>(1) );
    BOOST_CHECK_EQUAL( r2.denominator(), static_cast<T>(1) );
    BOOST_CHECK_EQUAL( r3.denominator(), static_cast<T>(1) );
    BOOST_CHECK_EQUAL( r4.denominator(), static_cast<T>(1) );
    BOOST_CHECK_EQUAL( r5.denominator(), static_cast<T>(2) );
    BOOST_CHECK_EQUAL( r6.denominator(), static_cast<T>(3) );
    BOOST_CHECK_EQUAL( r7.denominator(), static_cast<T>(3) );
    BOOST_CHECK_EQUAL( r8.denominator(), static_cast<T>(3) );
    BOOST_CHECK_EQUAL( r9.denominator(), static_cast<T>(5) );
}

// Assignment (non-operator) tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_assign_test, T, all_signed_test_types )
{
    my_configuration::hook<T>  h;
    boost::rational<T> &       r = h.r_[ 0 ];

    r.assign( 6, 8 );
    BOOST_CHECK_EQUAL( r.numerator(),   static_cast<T>(3) );
    BOOST_CHECK_EQUAL( r.denominator(), static_cast<T>(4) );

    r.assign( 0, -7 );
    BOOST_CHECK_EQUAL( r.numerator(),   static_cast<T>(0) );
    BOOST_CHECK_EQUAL( r.denominator(), static_cast<T>(1) );
}

// Comparison tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_comparison_test, T,
 all_signed_test_types )
{
    my_configuration::hook<T>  h;
    boost::rational<T>  &r1 = h.r_[ 0 ], &r2 = h.r_[ 1 ], &r3 = h.r_[ 2 ],
                        &r4 = h.r_[ 3 ], &r5 = h.r_[ 4 ], &r6 = h.r_[ 5 ],
                        &r7 = h.r_[ 6 ], &r8 = h.r_[ 7 ], &r9 = h.r_[ 8 ];

    BOOST_CHECK( r1 == r2 );
    BOOST_CHECK( r2 != r3 );
    BOOST_CHECK( r4 <  r3 );
    BOOST_CHECK( r4 <= r5 );
    BOOST_CHECK( r1 <= r2 );
    BOOST_CHECK( r5 >  r6 );
    BOOST_CHECK( r5 >= r6 );
    BOOST_CHECK( r7 >= r8 );

    BOOST_CHECK( !(r3 == r2) );
    BOOST_CHECK( !(r1 != r2) );
    BOOST_CHECK( !(r1 <  r2) );
    BOOST_CHECK( !(r5 <  r6) );
    BOOST_CHECK( !(r9 <= r2) );
    BOOST_CHECK( !(r8 >  r7) );
    BOOST_CHECK( !(r8 >  r2) );
    BOOST_CHECK( !(r4 >= r6) );

    BOOST_CHECK( r1 == static_cast<T>( 0) );
    BOOST_CHECK( r2 != static_cast<T>(-1) );
    BOOST_CHECK( r3 <  static_cast<T>( 2) );
    BOOST_CHECK( r4 <= static_cast<T>(-3) );
    BOOST_CHECK( r5 >  static_cast<T>( 3) );
    BOOST_CHECK( r6 >= static_cast<T>( 0) );

    BOOST_CHECK( static_cast<T>( 0) == r2 );
    BOOST_CHECK( static_cast<T>( 0) != r7 );
    BOOST_CHECK( static_cast<T>(-1) <  r8 );
    BOOST_CHECK( static_cast<T>(-2) <= r9 );
    BOOST_CHECK( static_cast<T>( 1) >  r1 );
    BOOST_CHECK( static_cast<T>( 1) >= r3 );
}

// Increment & decrement tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_1step_test, T, all_signed_test_types )
{
    my_configuration::hook<T>  h;
    boost::rational<T>  &r1 = h.r_[ 0 ], &r2 = h.r_[ 1 ], &r3 = h.r_[ 2 ],
                        &r7 = h.r_[ 6 ], &r8 = h.r_[ 7 ];

    BOOST_CHECK(   r1++ == r2 );
    BOOST_CHECK(   r1   != r2 );
    BOOST_CHECK(   r1   == r3 );
    BOOST_CHECK( --r1   == r2 );
    BOOST_CHECK(   r8-- == r7 );
    BOOST_CHECK(   r8   != r7 );
    BOOST_CHECK( ++r8   == r7 );
}

// Absolute value tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_abs_test, T, all_signed_test_types )
{
    typedef my_configuration::hook<T>           hook_type;
    typedef typename hook_type::rational_type   rational_type;

    hook_type      h;
    rational_type  &r2 = h.r_[ 1 ], &r5 = h.r_[ 4 ], &r8 = h.r_[ 7 ];

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
    // This is a nasty hack, required because some compilers do not implement
    // "Koenig Lookup."  Basically, if I call abs(r), the C++ standard says that
    // the compiler should look for a definition of abs in the namespace which
    // contains r's class (in this case boost)--among other places.

    using boost::abs;
#endif

    BOOST_CHECK_EQUAL( abs(r2), r2 );
    BOOST_CHECK_EQUAL( abs(r5), r5 );
    BOOST_CHECK_EQUAL( abs(r8), rational_type(2, 3) );
}

// Unary operator tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_unary_test, T, all_signed_test_types )
{
    my_configuration::hook<T>  h;
    boost::rational<T>         &r2 = h.r_[ 1 ], &r3 = h.r_[ 2 ],
                               &r4 = h.r_[ 3 ], &r5 = h.r_[ 4 ];

    BOOST_CHECK_EQUAL( +r5, r5 );

    BOOST_CHECK( -r3 != r3 );
    BOOST_CHECK_EQUAL( -(-r3), r3 );
    BOOST_CHECK_EQUAL( -r4, static_cast<T>(3) );

    BOOST_CHECK( !r2 );
    BOOST_CHECK( !!r3 );

    BOOST_CHECK( ! static_cast<bool>(r2) );
    BOOST_CHECK( r3 );
}

BOOST_AUTO_TEST_SUITE_END()


// The rational arithmetic operations suite
BOOST_AUTO_TEST_SUITE( rational_arithmetic_suite )

// Addition & subtraction tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_additive_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    BOOST_CHECK_EQUAL( rational_type( 1, 2) + rational_type(1, 2),
     static_cast<T>(1) );
    BOOST_CHECK_EQUAL( rational_type(11, 3) + rational_type(1, 2),
     rational_type( 25,  6) );
    BOOST_CHECK_EQUAL( rational_type(-8, 3) + rational_type(1, 5),
     rational_type(-37, 15) );
    BOOST_CHECK_EQUAL( rational_type(-7, 6) + rational_type(1, 7),
     rational_type(  1,  7) - rational_type(7, 6) );
    BOOST_CHECK_EQUAL( rational_type(13, 5) - rational_type(1, 2),
     rational_type( 21, 10) );
    BOOST_CHECK_EQUAL( rational_type(22, 3) + static_cast<T>(1),
     rational_type( 25,  3) );
    BOOST_CHECK_EQUAL( rational_type(12, 7) - static_cast<T>(2),
     rational_type( -2,  7) );
    BOOST_CHECK_EQUAL(    static_cast<T>(3) + rational_type(4, 5),
     rational_type( 19,  5) );
    BOOST_CHECK_EQUAL(    static_cast<T>(4) - rational_type(9, 2),
     rational_type( -1,  2) );

    rational_type  r( 11 );

    r -= rational_type( 20, 3 );
    BOOST_CHECK_EQUAL( r, rational_type(13,  3) );

    r += rational_type( 1, 2 );
    BOOST_CHECK_EQUAL( r, rational_type(29,  6) );

    r -= static_cast<T>( 5 );
    BOOST_CHECK_EQUAL( r, rational_type( 1, -6) );

    r += rational_type( 1, 5 );
    BOOST_CHECK_EQUAL( r, rational_type( 1, 30) );

    r += static_cast<T>( 2 );
    BOOST_CHECK_EQUAL( r, rational_type(61, 30) );
}

// Assignment tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_assignment_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    rational_type  r;

    r = rational_type( 1, 10 );
    BOOST_CHECK_EQUAL( r, rational_type( 1, 10) );

    r = static_cast<T>( -9 );
    BOOST_CHECK_EQUAL( r, rational_type(-9,  1) );
}

// Multiplication tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_multiplication_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    BOOST_CHECK_EQUAL( rational_type(1, 3) * rational_type(-3, 4),
     rational_type(-1, 4) );
    BOOST_CHECK_EQUAL( rational_type(2, 5) * static_cast<T>(7),
     rational_type(14, 5) );
    BOOST_CHECK_EQUAL(  static_cast<T>(-2) * rational_type(1, 6),
     rational_type(-1, 3) );

    rational_type  r = rational_type( 3, 7 );

    r *= static_cast<T>( 14 );
    BOOST_CHECK_EQUAL( r, static_cast<T>(6) );

    r *= rational_type( 3, 8 );
    BOOST_CHECK_EQUAL( r, rational_type(9, 4) );
}

// Division tests
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_division_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    BOOST_CHECK_EQUAL( rational_type(-1, 20) / rational_type(4, 5),
     rational_type(-1, 16) );
    BOOST_CHECK_EQUAL( rational_type( 5,  6) / static_cast<T>(7),
     rational_type( 5, 42) );
    BOOST_CHECK_EQUAL(     static_cast<T>(8) / rational_type(2, 7),
     static_cast<T>(28) );

    rational_type  r = rational_type( 4, 3 );

    r /= rational_type( 5, 4 );
    BOOST_CHECK_EQUAL( r, rational_type(16, 15) );

    r /= static_cast<T>( 4 );
    BOOST_CHECK_EQUAL( r, rational_type( 4, 15) );

    BOOST_CHECK_EQUAL( rational_type(-1) / rational_type(-3),
     rational_type(1, 3) );
}

// Tests for operations on self
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_self_operations_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    rational_type  r = rational_type( 4, 3 );

    r += r;
    BOOST_CHECK_EQUAL( r, rational_type( 8, 3) );

    r *= r;
    BOOST_CHECK_EQUAL( r, rational_type(64, 9) );

    r /= r;
    BOOST_CHECK_EQUAL( r, rational_type( 1, 1) );

    r -= r;
    BOOST_CHECK_EQUAL( r, rational_type( 0, 1) );
}

BOOST_AUTO_TEST_SUITE_END()


// The non-basic rational operations suite
BOOST_AUTO_TEST_SUITE( rational_extras_suite )

// Output test
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_output_test, T, all_signed_test_types )
{
    std::ostringstream  oss;
    
    oss << boost::rational<T>( 44, 14 );
    BOOST_CHECK_EQUAL( oss.str(), "22/7" );
}

// Input test, failing
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_input_failing_test, T,
 all_signed_test_types )
{
    std::istringstream  iss( "" );
    boost::rational<T>  r;

    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "42" );
    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "57A" );
    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "20-20" );
    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "1/" );
    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "1/ 2" );
    iss >> r;
    BOOST_CHECK( !iss );

    iss.clear();
    iss.str( "1 /2" );
    iss >> r;
    BOOST_CHECK( !iss );
}

// Input test, passing
BOOST_AUTO_TEST_CASE_TEMPLATE( rational_input_passing_test, T,
 all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    std::istringstream  iss( "1/2 12" );
    rational_type       r;
    int                 n = 0;

    BOOST_CHECK( iss >> r >> n );
    BOOST_CHECK_EQUAL( r, rational_type(1, 2) );
    BOOST_CHECK_EQUAL( n, 12 );

    iss.clear();
    iss.str( "34/67" );
    BOOST_CHECK( iss >> r );
    BOOST_CHECK_EQUAL( r, rational_type(34, 67) );

    iss.clear();
    iss.str( "-3/-6" );
    BOOST_CHECK( iss >> r );
    BOOST_CHECK_EQUAL( r, rational_type(1, 2) );
}

// Conversion test
BOOST_AUTO_TEST_CASE( rational_cast_test )
{
    // Note that these are not generic.  The problem is that rational_cast<T>
    // requires a conversion from IntType to T.  However, for a user-defined
    // IntType, it is not possible to define such a conversion except as an
    // "operator T()".  This causes problems with overloading resolution.
    boost::rational<int> const  half( 1, 2 );

    BOOST_CHECK_CLOSE( boost::rational_cast<double>(half), 0.5, 0.01 );
    BOOST_CHECK_EQUAL( boost::rational_cast<int>(half), 0 );
    BOOST_CHECK_EQUAL( boost::rational_cast<MyInt>(half), MyInt() );
}

// Dice tests (a non-main test)
BOOST_AUTO_TEST_CASE_TEMPLATE( dice_roll_test, T, all_signed_test_types )
{
    typedef boost::rational<T>  rational_type;

    // Determine the mean number of times a fair six-sided die
    // must be thrown until each side has appeared at least once.
    rational_type  r = T( 0 );

    for ( int  i = 1 ; i <= 6 ; ++i )
    {
        r += rational_type( 1, i );
    }
    r *= static_cast<T>( 6 );

    BOOST_CHECK_EQUAL( r, rational_type(147, 10) );
}

BOOST_AUTO_TEST_SUITE_END()
