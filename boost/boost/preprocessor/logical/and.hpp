#ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#define BOOST_PREPROCESSOR_LOGICAL_AND_HPP

/* Copyright (C) 2001
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

#include <boost/preprocessor/logical/not.hpp>

/** <p>Expands to the logical AND of the operands.</p>

<p>For example, <code>BOOST_PP_AND(0,5)</code> expands to <code>0</code> (a single token).</p>
*/
#define BOOST_PP_AND(X,Y) BOOST_PP_NOR(BOOST_PP_NOT(X),BOOST_PP_NOT(Y))

/** <p>Obsolete. Use BOOST_PP_AND().</p> */
#define BOOST_PREPROCESSOR_AND(X,Y) BOOST_PP_AND(X,Y)
#endif
