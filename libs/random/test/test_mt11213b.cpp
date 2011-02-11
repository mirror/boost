/* test_mt11213b.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/mersenne_twister.hpp>

#define BOOST_RANDOM_URNG boost::random::mt11213b
#define BOOST_RANDOM_VALIDATION_VALUE 3809585648U

#include "test_generator.ipp"
