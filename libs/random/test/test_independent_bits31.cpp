/* test_independent_bits31.cpp
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
#include <boost/random/linear_congruential.hpp>

typedef boost::random::independent_bits_engine<boost::random::minstd_rand0, 31, boost::uint32_t> independent_bits31;
#define BOOST_RANDOM_URNG independent_bits31
#define BOOST_RANDOM_VALIDATION_VALUE 26292962

#include "test_generator.ipp"
