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
typename PRNG::result_type validation_value()
{
    PRNG rng;
    for(int i = 0; i < 9999; i++)
        rng();
    return rng();
}

int test_main(int, char*[])
{
    // own run
    BOOST_CHECK_EQUAL(validation_value<boost::mt11213b>(), 3809585648U);

    // validation by experiment from mt19937.c
    BOOST_CHECK_EQUAL(validation_value<boost::mt19937>(), 4123659995U);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    // validation from the C++0x draft (n3090)
    BOOST_CHECK_EQUAL(validation_value<boost::mt19937_64>(), UINT64_C(9981545732273789042));
#endif

    // validation values from the publications
    BOOST_CHECK_EQUAL(validation_value<boost::minstd_rand0>(), 1043618065);

    // validation values from the publications
    BOOST_CHECK_EQUAL(validation_value<boost::minstd_rand>(), 399268537);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    // by experiment from lrand48()
    BOOST_CHECK_EQUAL(validation_value<boost::rand48>(), 1993516219);
#endif

    // ????
    BOOST_CHECK_EQUAL(validation_value<boost::taus88>(), 3535848941U);

    // ????
    BOOST_CHECK_EQUAL(validation_value<boost::ecuyer1988>(), 2060321752);

    // validation by experiment from Harry Erwin's generator.h (private e-mail)
    BOOST_CHECK_EQUAL(validation_value<boost::kreutzer1986>(), 139726);

    // validation from the C++0x draft (n3090)
    BOOST_CHECK_EQUAL(validation_value<boost::random::knuth_b>(), 1112339016);

    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci607>(), 0.401269, 1e-5);

    // principal operation validated with CLHEP, values by experiment
    BOOST_CHECK_EQUAL(validation_value<boost::ranlux3>(), 5957620);
    BOOST_CHECK_EQUAL(validation_value<boost::ranlux4>(), 8587295);

    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::ranlux3_01>(), 5957620/std::pow(2.0f,24), 1e-6);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::ranlux4_01>(), 8587295/std::pow(2.0f,24), 1e-6);

    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::ranlux64_3_01>(), 0.838413, 1e-6);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::ranlux64_4_01>(), 0.59839, 1e-6);

    BOOST_CHECK_EQUAL(validation_value<boost::random::ranlux24>(), 9901578);

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
    BOOST_CHECK_EQUAL(validation_value<boost::random::ranlux48>(), UINT64_C(249142670248501));
#endif

    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci607>(), 0.40126853196520074, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci1279>(), 0.56576990947654049, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci2281>(), 0.85870032418398168, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci3217>(), 0.29923216793615537, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci4423>(), 0.39798595467394815, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci9689>(), 0.22728966337376244, 1e-14);

    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci19937>(), 0.21779661133680173, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci23209>(), 0.98718042717052668, 1e-14);
    BOOST_CHECK_CLOSE_FRACTION(validation_value<boost::lagged_fibonacci44497>(), 0.86191789886161496, 1e-14);
    
    typedef boost::random::lagged_fibonacci_engine<boost::uint32_t, 24, 607, 273> lagged_fibonacci;
    BOOST_CHECK_EQUAL(validation_value<lagged_fibonacci>(), 3543833);

    return 0;
}
