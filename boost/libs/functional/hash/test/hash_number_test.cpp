
//  Copyright Daniel James 2005. Use, modification, and distribution are
//  subject to the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/functional/hash/hash.hpp>

#define BOOST_AUTO_TEST_MAIN
#include <boost/test/auto_unit_test.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/limits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

#include "./compile_time.hpp"

template <class T>
void numeric_test()
{
    BOOST_CHECK(compile_time_tests<T>::success);

    boost::hash<T> x1;
    boost::hash<T> x2;

    BOOST_CHECK_EQUAL(x1(T(0)), x2(T(0)));

    BOOST_CHECK_EQUAL(x1(T(10)), x2(T(10)));
    BOOST_CHECK_EQUAL(x1(T(25)), x2(T(25)));

    BOOST_CHECK_EQUAL(x1(T(5) - T(5)), x2(T(0)));
    BOOST_CHECK_EQUAL(x1(T(6) + T(4)), x2(T(10)));

    typedef std::numeric_limits<T> limits;
    BOOST_CHECK(limits::is_specialized);

    BOOST_CHECK_EQUAL(x1((limits::min)()), x2((limits::min)()));
    BOOST_CHECK_EQUAL(x1((limits::max)()), x2((limits::max)()));

    // A hash function can legally fail these tests, but it'll not be a good
    // sign.
    if(T(1) != T(-1))
        BOOST_CHECK(x1(T(1)) !=  x2(T(-1)));
    if(T(1) != T(2))
        BOOST_CHECK(x1(T(1)) !=  x2(T(2)));
    if((limits::max)() != (limits::max)() - 1)
        BOOST_CHECK(x1((limits::max)()) != x2((limits::max)() - 1));
}

#define NUMERIC_TEST(type, name) \
    BOOST_AUTO_UNIT_TEST(BOOST_PP_CAT(test_, name)) { \
        numeric_test<type>(); \
    }

NUMERIC_TEST(bool, bool)
NUMERIC_TEST(char, char)
NUMERIC_TEST(signed char, schar)
NUMERIC_TEST(unsigned char, uchar)
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
NUMERIC_TEST(wchar_t, wchar)
#endif
NUMERIC_TEST(short, short)
NUMERIC_TEST(unsigned short, ushort)
NUMERIC_TEST(int, int)
NUMERIC_TEST(unsigned int, uint)
NUMERIC_TEST(long, hash_long)
NUMERIC_TEST(unsigned long, ulong)
NUMERIC_TEST(float, float)
NUMERIC_TEST(double, double)
NUMERIC_TEST(long double, ldouble)
