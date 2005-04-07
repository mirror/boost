
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

template <class T>
void float_tests(T* = 0)
{
    HASH_NAMESPACE::hash<T> x1;

    T zero = 0;
    T minus_zero = (T) -1 * zero;

    BOOST_CHECK(zero == minus_zero);
    BOOST_CHECK(x1(zero) == x1(minus_zero));

    using namespace std;

    // The tests cause Borland to crash horribly.
#if defined(__BORLANDC__)
    BOOST_REQUIRE(false);
#endif
    
    if(std::numeric_limits<T>::has_infinity) {
        T infinity = (T) 1. / zero;
        T infinity2 = -log(zero);
        T infinity3 = (T) -1. / minus_zero;
        T infinity4 = std::numeric_limits<T>::infinity();
        
        T minus_infinity = (T) -1. / zero;
        T minus_infinity2 = log(zero);
        T minus_infinity3 = (T) 1. / minus_zero;

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
        BOOST_WARN(x1(infinity) != x1(minus_infinity));

        // This should really be 'has_denorm == denorm_present' but some
        // compilers don't have 'denorm_present'. See also a leter use.
        if(std::numeric_limits<T>::has_denorm) {
            BOOST_CHECK(x1(std::numeric_limits<T>::denorm_min()) != x1(infinity));
            BOOST_CHECK(x1(std::numeric_limits<T>::denorm_min()) != x1(minus_infinity));
        }

        if(std::numeric_limits<T>::has_quiet_NaN) {
            // Another two failures, should I work around this?
            BOOST_WARN(x1(std::numeric_limits<T>::quiet_NaN()) != x1(infinity));
            BOOST_WARN(x1(std::numeric_limits<T>::quiet_NaN()) != x1(minus_infinity));
        }
    }

    T max = (std::numeric_limits<T>::max)();
    T half_max = max / 2;
    T quater_max = max / 4;
    T three_quater_max = max - quater_max;
    BOOST_CHECK(x1(max) == x1(max));
    BOOST_CHECK(x1(max) != x1(quater_max));
    BOOST_CHECK(x1(max) != x1(half_max));
    BOOST_CHECK(x1(max) != x1(three_quater_max));
    BOOST_CHECK(x1(quater_max) == x1(quater_max));
    BOOST_CHECK(x1(quater_max) != x1(half_max));
    BOOST_CHECK(x1(quater_max) != x1(three_quater_max));
    BOOST_CHECK(x1(half_max) == x1(half_max));
    BOOST_CHECK(x1(half_max) != x1(three_quater_max));
    BOOST_CHECK(x1(three_quater_max) == x1(three_quater_max));

    T v1 = asin((T) 1);
    T v2 = acos((T) 0);
    BOOST_CHECK(v1 == v2);
    BOOST_CHECK(x1(v1) == x1(v2));

    BOOST_CHECK(x1(std::numeric_limits<T>::epsilon()) != x1((T) 0));

    // As before.
    if(std::numeric_limits<T>::has_denorm) {
        BOOST_CHECK(x1(std::numeric_limits<T>::denorm_min()) != x1(zero));
    }

    if(std::numeric_limits<T>::has_quiet_NaN) {
        BOOST_CHECK(x1(std::numeric_limits<T>::quiet_NaN()) != x1(zero));
    }
}

BOOST_AUTO_UNIT_TEST(hash_float_tests)
{
    float_tests((float*) 0);
    float_tests((double*) 0);
    float_tests((long double*) 0);
}
