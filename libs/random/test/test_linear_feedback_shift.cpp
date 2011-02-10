/* test_linear_feedback_shift.cpp
 *
 * Copyright Steven Watanabe 2011
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * $Id$
 *
 */

#include <boost/random/linear_feedback_shift.hpp>

typedef boost::random::linear_feedback_shift_engine<boost::uint32_t, 32, 31, 13, 12> linear_feedback_shift;
#define BOOST_RANDOM_URNG linear_feedback_shift
#define BOOST_RANDOM_VALIDATION_VALUE 981440277

#include "test_generator.ipp"
