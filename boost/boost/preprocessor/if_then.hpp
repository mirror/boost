#ifndef BOOST_PREPROCESSOR_IF_THEN_HPP
#define BOOST_PREPROCESSOR_IF_THEN_HPP

/* Copyright (C) 2002
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/if.hpp>

/** <p>Expands to <code>T</code> if <code>C != 0</code> and to nothing if <code>C == 0</code>.</p>
*/
#define BOOST_PP_IF_THEN(C,T) BOOST_PP_IF(C,T BOOST_PP_EMPTY,BOOST_PP_EMPTY)()
#endif
