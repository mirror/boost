/* test_rand48.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/linear_congruential.hpp>
#include <boost/cstdint.hpp>

#define BOOST_RANDOM_URNG boost::random::rand48
// by experiment from lrand48()
#define BOOST_RANDOM_VALIDATION_VALUE 1993516219

// rand48 uses non-standard seeding
template<class Converted, class T>
void test_seed_conversion(boost::rand48 & urng, const T & t) {
    boost::rand48 urng2(t);
    urng2.seed(t);
}

#include "test_generator.ipp"
