/* test_independent_bits32.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/independent_bits.hpp>
#include <boost/random/mersenne_twister.hpp>

typedef boost::random::independent_bits_engine<boost::random::mt19937, 32, boost::uint32_t> independent_bits32;
#define BOOST_RANDOM_URNG independent_bits32
#define BOOST_RANDOM_VALIDATION_VALUE 4123659995U

#include "test_generator.ipp"
