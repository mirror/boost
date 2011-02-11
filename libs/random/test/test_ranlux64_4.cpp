/* test_ranlux64_4.cpp
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

#define BOOST_RANDOM_URNG boost::random::ranlux64_4
// principal operation validated with CLHEP, values by experiment
#define BOOST_RANDOM_VALIDATION_VALUE 199461971133682

#include "test_generator.ipp"
