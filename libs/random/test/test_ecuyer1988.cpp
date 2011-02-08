/* test_ecuyer1988.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/additive_combine.hpp>

#define BOOST_RANDOM_URNG boost::random::ecuyer1988

#include "test_generator.ipp"
