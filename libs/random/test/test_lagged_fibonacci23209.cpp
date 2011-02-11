/* test_lagged_fibonacci23209.cpp
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

#define BOOST_RANDOM_URNG boost::random::lagged_fibonacci23209
#define BOOST_RANDOM_VALIDATION_VALUE 0.98718042717052668

#include "test_generator.ipp"
