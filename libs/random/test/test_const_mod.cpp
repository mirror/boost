/* test_const_mod.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/detail/const_mod.hpp>

#include <boost/mpl/vector.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

typedef boost::mpl::vector<
    boost::int8_t,
    boost::uint8_t
> int8_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult8, IntType, int8_types) {
    for(int i = 0; i < 127; ++i) {
        for(int j = 0; j < 127; ++j) {
            BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 127>::mult(IntType(i), IntType(j))), i * j % 127);
        }
    }
    int modulus = (std::numeric_limits<IntType>::max)() + 1;
    for(int i = 0; i < modulus; ++i) {
        for(int j = 0; j < modulus; ++j) {
            BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 0>::mult(IntType(i), IntType(j))), i * j % modulus);
        }
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_add8, IntType, int8_types) {
    for(int i = 0; i < 127; ++i) {
        for(int j = 0; j < 127; ++j) {
            BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 127>::add(IntType(i), IntType(j))), (i + j) % 127);
        }
    }
    {
    const int modulus = boost::integer_traits<IntType>::const_max;
    for(int i = 0; i < modulus; ++i) {
        for(int j = 0; j < modulus; ++j) {
            BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, modulus>::add(IntType(i), IntType(j))), (i + j) % modulus);
        }
    }
    }
    {
    int modulus = (std::numeric_limits<IntType>::max)() + 1;
    for(int i = 0; i < modulus; ++i) {
        for(int j = 0; j < modulus; ++j) {
            BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 0>::add(IntType(i), IntType(j))), (i + j) % modulus);
        }
    }
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_add8, IntType, int8_types) {
    for(int i = 0; i < 127; i += 5) {
        for(int j = 0; j < 127; j += 3) {
            for(int k = 0; k < 127; k += 3) {
                BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 127>::mult_add(IntType(i), IntType(j), IntType(k))), (i * j + k) % 127);
            }
        }
    }
    {
    int modulus = (std::numeric_limits<IntType>::max)() + 1;
    for(int i = 0; i < modulus; i += 5) {
        for(int j = 0; j < modulus; j += 3) {
            for(int k = 0; k < modulus; k += 3) {
                BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 0>::mult_add(IntType(i), IntType(j), IntType(k))), (i * j + k) % modulus);
            }
        }
    }
    }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_invert8, IntType, int8_types) {
    for(int i = 1; i < 127; ++i) {
        IntType inverse = boost::random::const_mod<IntType, 127>::invert(IntType(i));
        BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 127>::mult(IntType(i), inverse)), 1);
    }
    int modulus = (std::numeric_limits<IntType>::max)() + 1;
    for(int i = 1; i < modulus; i += 2) {
        IntType inverse = boost::random::const_mod<IntType, 0>::invert(IntType(i));
        BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 0>::mult(IntType(i), inverse)), 1);
    }
}

typedef boost::mpl::vector<
    boost::int32_t,
    boost::uint32_t
> int32_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult32, IntType, int32_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(0, 2147483562)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(2147483562, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(2147483562, 2147483562)), 1);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(1234567890, 1234657890)), 813106682);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_add32, IntType, int32_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::add(0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::add(0, 2147483562)), 2147483562);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::add(2147483562, 0)), 2147483562);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::add(2147483562, 2147483562)), 2147483561);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::add(1234567890, 1234657890)), 321742217);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_add32, IntType, int32_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(0, 0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(0, 2147483562, 827364)), 827364);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(2147483562, 0, 827364)), 827364);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(2147483562, 2147483562, 2147483562)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(1234567890, 1234657890, 1726384759)), 392007878);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_invert32, IntType, int32_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::invert(0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult_add(0, 0, 0)), 0);
    IntType inverse;
    inverse = boost::random::const_mod<IntType, 2147483563>::invert(2147483562);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(2147483562, inverse)), 1);
    inverse = boost::random::const_mod<IntType, 2147483563>::invert(1234567890);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563>::mult(1234567890, inverse)), 1);
}

#if !defined(BOOST_NO_INT64_T)

typedef boost::mpl::vector<
    boost::int64_t,
    boost::uint64_t
> int64_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult64, IntType, int64_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(0, 2147483562)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(2147483562, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(2147483562, 2147483562)), 316718521754730848);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(1234567890, 1234657890)), 1524268986129152100);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(1234567890726352938, 1234657890736453927)), 88656187017794672);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_add64, IntType, int64_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(0, 2147483562)), 2147483562);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(2147483562, 0)), 2147483562);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(2147483562, 2147483562)), 4294967124);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(1234567890, 1234657890)), 2469225780);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(1234567890726352938, 1234657890736453927)), 321742217810068367);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::add(2147483563652738490, 8)), 0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_mult_add64, IntType, int64_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(0, 0, 0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(0, 2147483562, 827364)), 827364);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(2147483562, 0, 827364)), 827364);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(2147483562, 2147483562, 2147483562)), 316718523902214410);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(1234567890, 1234657890, 1726384759)), 1524268987855536859);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(1234567890726352938, 1234657890736453927, 1726384759726488649)), 1815040946744283321);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_invert64, IntType, int64_types) {
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::invert(0)), 0);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult_add(0, 0, 0)), 0);
    IntType inverse;
    inverse = boost::random::const_mod<IntType, 2147483563652738498>::invert(7362947769);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(7362947769, inverse)), 1);
    inverse = boost::random::const_mod<IntType, 2147483563652738498>::invert(1263142436887493875);
    BOOST_CHECK_EQUAL((boost::random::const_mod<IntType, 2147483563652738498>::mult(1263142436887493875, inverse)), 1);
}

#endif
