/* boost validate.cpp
 *
 * Copyright Jens Maurer 2000
 * Copyright Steven Watanabe 2010-2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 */

#include <cmath>
#include <boost/random.hpp>
#include <boost/config.hpp>

#include <boost/test/test_tools.hpp>
#include <boost/test/included/test_exec_monitor.hpp>

/*
 * Validate correct implementation
 */

template<class PRNG>
typename PRNG::result_type validation_value(PRNG rng)
{
    for(int i = 0; i < 9999; i++)
        rng();
    return rng();
}

int test_main(int, char*[])
{
    // own run
    BOOST_CHECK_EQUAL(validation_value(boost::mt11213b()), 3809585648U);

    // validation by experiment from mt19937.c
    BOOST_CHECK_EQUAL(validation_value(boost::mt19937()), 4123659995U);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    // validation from the C++0x draft (n3090)
    BOOST_CHECK_EQUAL(validation_value(boost::mt19937_64()), UINT64_C(9981545732273789042));
#endif

    // validation values from the publications
    BOOST_CHECK_EQUAL(validation_value(boost::minstd_rand0()), 1043618065);

    // validation values from the publications
    BOOST_CHECK_EQUAL(validation_value(boost::minstd_rand()), 399268537);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    // by experiment from lrand48()
    BOOST_CHECK_EQUAL(validation_value(boost::rand48()), 1993516219);
#endif

    // ????
    BOOST_CHECK_EQUAL(validation_value(boost::taus88()), 3535848941U);

    // ????
    BOOST_CHECK_EQUAL(validation_value(boost::ecuyer1988()), 2060321752);

    // validation by experiment from Harry Erwin's generator.h (private e-mail)
    BOOST_CHECK_EQUAL(validation_value(boost::kreutzer1986()), 139726);

    // validation from the C++0x draft (n3090)
    BOOST_CHECK_EQUAL(validation_value(boost::random::knuth_b()), 1112339016);

    BOOST_CHECK_CLOSE_FRACTION(validation_value(boost::lagged_fibonacci607()), 0.401269, 1e-5);

    // principal operation validated with CLHEP, values by experiment
    BOOST_CHECK_EQUAL(validation_value(boost::ranlux3()), 5957620);
    BOOST_CHECK_EQUAL(validation_value(boost::ranlux4()), 8587295);

    BOOST_CHECK_CLOSE_FRACTION(validation_value(boost::ranlux3_01()), 5957620/std::pow(2.0f,24), 1e-6);
    BOOST_CHECK_CLOSE_FRACTION(validation_value(boost::ranlux4_01()), 8587295/std::pow(2.0f,24), 1e-6);

    BOOST_CHECK_CLOSE_FRACTION(validation_value(boost::ranlux64_3_01()), 0.838413, 1e-6);
    BOOST_CHECK_CLOSE_FRACTION(validation_value(boost::ranlux64_4_01()), 0.59839, 1e-6);

    BOOST_CHECK_EQUAL(validation_value(boost::random::ranlux24()), 9901578);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    BOOST_CHECK_EQUAL(validation_value(boost::random::ranlux48()), UINT64_C(249142670248501));
#endif

    return 0;
}
