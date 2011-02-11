/* test_ranlux24_base.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/ranlux.hpp>

#define BOOST_RANDOM_URNG boost::random::ranlux24_base
// validation from the C++0x draft (n3126).
#define BOOST_RANDOM_VALIDATION_VALUE 7937952

#include "test_generator.ipp"
