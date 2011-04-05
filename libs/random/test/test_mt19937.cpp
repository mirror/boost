/* test_mt19937.cpp
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

#define BOOST_RANDOM_URNG boost::random::mt19937

#define BOOST_RANDOM_SEED_WORDS 624

// validation by experiment from mt19937.c
#define BOOST_RANDOM_VALIDATION_VALUE 4123659995U
#define BOOST_RANDOM_SEED_SEQ_VALIDATION_VALUE 3107690757U
#define BOOST_RANDOM_ITERATOR_VALIDATION_VALUE 3408548740U

#define BOOST_RANDOM_GENERATE_VALUES { 0xD091BB5CU, 0x22AE9EF6U, 0xE7E1FAEEU, 0xD5C31F79U }

#include "test_generator.ipp"
