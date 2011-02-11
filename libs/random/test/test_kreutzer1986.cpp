/* test_kreutzer1986.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/shuffle_order.hpp>
#include <boost/cstdint.hpp>

#define BOOST_RANDOM_URNG boost::random::kreutzer1986
// validation by experiment from Harry Erwin's generator.h (private e-mail)
#define BOOST_RANDOM_VALIDATION_VALUE 139726

#include "test_generator.ipp"
