/* test_knuth_b.cpp
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

#define BOOST_RANDOM_URNG boost::random::knuth_b
// validation from the C++0x draft (n3090)
#define BOOST_RANDOM_VALIDATION_VALUE 1112339016

#include "test_generator.ipp"
