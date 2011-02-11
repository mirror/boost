/* test_ranlux3_01.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/ranlux.hpp>
#include <cmath>

#define BOOST_RANDOM_URNG boost::random::ranlux3_01
// principal operation validated with CLHEP, values by experiment
#define BOOST_RANDOM_VALIDATION_VALUE 5957620/std::pow(2.0f,24)

#include "test_generator.ipp"
