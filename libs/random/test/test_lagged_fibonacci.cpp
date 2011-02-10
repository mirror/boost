/* test_lagged_fibonacci.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/lagged_fibonacci.hpp>

typedef boost::random::lagged_fibonacci_engine<boost::uint32_t, 24, 607, 273> lagged_fibonacci;
#define BOOST_RANDOM_URNG lagged_fibonacci
#define BOOST_RANDOM_VALIDATION_VALUE 3543833

#include "test_generator.ipp"
