
//  Copyright Daniel James 2005. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "./config.hpp"

#ifdef TEST_STD_INCLUDES
#  include <functional>
#else
#  include <boost/functional/hash/hash.hpp>
#endif

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <cmath>
#include <boost/limits.hpp>

#include <iostream>

template <class T>
void float_tests(char const* name, T* = 0)
{
    std::cout<<"\n"
        "Testing " BOOST_STRINGIZE(HASH_NAMESPACE) "::hash<"<<name<<">\n"
        "\n";

    HASH_NAMESPACE::hash<T> x1;

    T zero = 0;
    T minus_zero = (T) -1 * zero;

    BOOST_CHECK(zero == minus_zero);
    BOOST_CHECK(x1(zero) == x1(minus_zero));

    BOOST_CHECK(x1(zero) == HASH_NAMESPACE::hash_value(zero));
    BOOST_CHECK(x1(minus_zero) == HASH_NAMESPACE::hash_value(minus_zero));

    using namespace std;

// Doing anything with infinity causes borland to crash.
#if defined(__BORLANDC__)
    std::cout<<"Not running infinity checks on Borland, as it causes it to crash.\n";
#else
    if(std::numeric_limits<T>::has_infinity) {
        T infinity = -log(zero);
        T infinity2 = (T) 1. / zero;
        T infinity3 = (T) -1. / minus_zero;
        T infinity4 = std::numeric_limits<T>::infinity();

        T minus_infinity = log(zero);
        T minus_infinity2 = (T) -1. / zero;
        T minus_infinity3 = (T) 1. / minus_zero;

        BOOST_CHECK(x1(infinity) == HASH_NAMESPACE::hash_value(infinity));
        BOOST_CHECK(x1(minus_infinity)
                == HASH_NAMESPACE::hash_value(minus_infinity));

        BOOST_CHECK(infinity == infinity2);
        BOOST_CHECK(infinity == infinity3);
        BOOST_CHECK(infinity == infinity4);
        BOOST_CHECK(x1(infinity) == x1(infinity2));
        BOOST_CHECK(x1(infinity) == x1(infinity3));
        BOOST_CHECK(x1(infinity) == x1(infinity4));

        BOOST_CHECK(minus_infinity == minus_infinity2);
        BOOST_CHECK(x1(minus_infinity) == x1(minus_infinity2));
        BOOST_CHECK(minus_infinity == minus_infinity3);
        BOOST_CHECK(x1(minus_infinity) == x1(minus_infinity3));

        BOOST_CHECK(infinity != minus_infinity);

        // My hash fails this one, I guess it's not that bad.
        if(x1(infinity) == x1(minus_infinity)) {
            std::cout<<"x1(infinity) == x1(-infinity) == "<<x1(infinity)<<"\n";
        }

        // This should really be 'has_denorm == denorm_present' but some
        // compilers don't have 'denorm_present'. See also a later use.
        if(std::numeric_limits<T>::has_denorm) {
            if(x1(std::numeric_limits<T>::denorm_min()) == x1(infinity)) {
                std::cout<<"x1(denorm_min) == x1(infinity) == "<<x1(infinity)<<"\n";
            }
            if(x1(std::numeric_limits<T>::denorm_min()) == x1(minus_infinity)) {
                std::cout<<"x1(denorm_min) == x1(-infinity) == "<<x1(minus_infinity)<<"\n";
            }
        }

        if(std::numeric_limits<T>::has_quiet_NaN) {
            if(x1(std::numeric_limits<T>::quiet_NaN()) == x1(infinity)) {
                std::cout<<"x1(quiet_NaN) == x1(infinity) == "<<x1(infinity)<<"\n";
            }
            if(x1(std::numeric_limits<T>::quiet_NaN()) == x1(minus_infinity)) {
                std::cout<<"x1(quiet_NaN) == x1(-infinity) == "<<x1(minus_infinity)<<"\n";
            }
        }
    }
#endif

    T max = (std::numeric_limits<T>::max)();
    T half_max = max / 2;
    T quarter_max = max / 4;
    T three_quarter_max = max - quarter_max;

    BOOST_CHECK(x1(max) == HASH_NAMESPACE::hash_value(max));
    BOOST_CHECK(x1(half_max) == HASH_NAMESPACE::hash_value(half_max));
    BOOST_CHECK(x1(quarter_max) == HASH_NAMESPACE::hash_value(quarter_max));
    BOOST_CHECK(x1(three_quarter_max) == HASH_NAMESPACE::hash_value(three_quarter_max));

    // The '!=' tests could legitimately fail, but with my hash it indicates a bug.
    BOOST_CHECK(x1(max) == x1(max));
    BOOST_CHECK(x1(max) != x1(quarter_max));
    BOOST_CHECK(x1(max) != x1(half_max));
    BOOST_CHECK(x1(max) != x1(three_quarter_max));
    BOOST_CHECK(x1(quarter_max) == x1(quarter_max));
    BOOST_CHECK(x1(quarter_max) != x1(half_max));
    BOOST_CHECK(x1(quarter_max) != x1(three_quarter_max));
    BOOST_CHECK(x1(half_max) == x1(half_max));
    BOOST_CHECK(x1(half_max) != x1(three_quarter_max));
    BOOST_CHECK(x1(three_quarter_max) == x1(three_quarter_max));

    T v1 = asin((T) 1);
    T v2 = acos((T) 0);
    if(v1 == v2)
        BOOST_CHECK(x1(v1) == x1(v2));
    BOOST_CHECK(x1(v1) == HASH_NAMESPACE::hash_value(v1));
    BOOST_CHECK(x1(v2) == HASH_NAMESPACE::hash_value(v2));

    BOOST_CHECK(x1(std::numeric_limits<T>::epsilon()) != x1((T) 0));
    BOOST_CHECK(x1(std::numeric_limits<T>::epsilon()) ==
            HASH_NAMESPACE::hash_value(std::numeric_limits<T>::epsilon()));

    // As before.
    if(std::numeric_limits<T>::has_denorm) {
        if(x1(std::numeric_limits<T>::denorm_min()) == x1(zero)) {
            std::cout<<"x1(denorm_min) == x1(zero) == "<<x1(zero)<<"\n";
        }
        BOOST_CHECK_MESSAGE(x1(std::numeric_limits<T>::denorm_min()) ==
            HASH_NAMESPACE::hash_value(std::numeric_limits<T>::denorm_min()),
            "x1(std::numeric_limits<T>::denorm_min()) = "
                << x1(std::numeric_limits<T>::denorm_min())
                << "\nhash_value(std::numeric_limits<T>::denorm_min()) = "
                << HASH_NAMESPACE::hash_value(
                    std::numeric_limits<T>::denorm_min())
                << "\nx1(0) = "<<x1(0)<<"\n");
    }

// NaN also causes borland to crash.
#if !defined(__BORLANDC__)
    if(std::numeric_limits<T>::has_quiet_NaN) {
        if(x1(std::numeric_limits<T>::quiet_NaN()) == x1(1.0)) {
            std::cout<<"x1(quiet_NaN) == x1(1.0) == "<<x1(1.0)<<"\n";
        }
        BOOST_CHECK(x1(std::numeric_limits<T>::quiet_NaN()) ==
            HASH_NAMESPACE::hash_value(std::numeric_limits<T>::quiet_NaN()));
    }
#endif
}

BOOST_AUTO_UNIT_TEST(hash_float_tests)
{
    std::cout<<"Compiler: "<<BOOST_COMPILER<<"\n";
    std::cout<<"Platform: "<<BOOST_PLATFORM<<"\n";
    std::cout<<"Library: "<<BOOST_STDLIB<<"\n\n";

    float_tests("float", (float*) 0);
}

BOOST_AUTO_UNIT_TEST(hash_double_tests)
{
    float_tests("double", (double*) 0);
}

BOOST_AUTO_UNIT_TEST(hash_long_double_tests)
{
    float_tests("long double", (long double*) 0);
}
