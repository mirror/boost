/* boost random/ranlux.hpp header file
 *
 * Copyright Jens Maurer 2002
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation,
 *
 * Jens Maurer makes no representations about the suitability of this
 * software for any purpose. It is provided "as is" without express or
 * implied warranty.
 *
 * See http://www.boost.org for most recent version including documentation.
 *
 * $Id$
 *
 * Revision history
 *  2001-02-18  created
 */

#ifndef BOOST_RANDOM_RANLUX_HPP
#define BOOST_RANDOM_RANLUX_HPP

#include <boost/config.hpp>
#include <boost/random/subtract_with_carry.hpp>
#include <boost/random/discard_block.hpp>

namespace boost {

typedef random::discard_block<random::ranlux_base, 218, 24, 0> ranlux_4;
typedef random::discard_block<random::ranlux_base, 404, 24, 0> ranlux_7;
typedef random::discard_block<random::ranlux_base, 794, 24, 0> ranlux_14;

#if !defined(BOOST_NO_INT64_T) && !defined(BOOST_NO_INTEGRAL_INT64_T)
typedef random::discard_block<random::ranlux64_base, 218, 24, 0> ranlux64_4;
typedef random::discard_block<random::ranlux64_base, 404, 24, 0> ranlux64_7;
typedef random::discard_block<random::ranlux64_base, 794, 24, 0> ranlux64_14;
#endif /* !BOOST_NO_INT64_T && !BOOST_NO_INTEGRAL_INT64_T */

} // namespace boost

#endif // BOOST_RANDOM_LINEAR_CONGRUENTIAL_HPP
