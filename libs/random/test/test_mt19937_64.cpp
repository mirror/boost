/* test_mt119937_64.cpp
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
#include <boost/cstdint.hpp>

#define BOOST_RANDOM_URNG boost::random::mt19937_64
// validation from the C++0x draft (n3090)
#define BOOST_RANDOM_VALIDATION_VALUE UINT64_C(9981545732273789042)

#include "test_generator.ipp"
