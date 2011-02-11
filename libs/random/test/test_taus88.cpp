/* test_taus88.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/taus88.hpp>

#define BOOST_RANDOM_URNG boost::random::taus88
#define BOOST_RANDOM_VALIDATION_VALUE 3535848941U

#include "test_generator.ipp"
