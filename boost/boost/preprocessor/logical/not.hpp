#ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#define BOOST_PREPROCESSOR_LOGICAL_NOT_HPP

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

#include <boost/preprocessor/logical/nor.hpp>

/** <P>Expands to the logical NOT of the operand.</P>

<P>For example, BOOST_PP_NOT(0) expands to 1 (a single token).</P>
*/
#define BOOST_PP_NOT(X) BOOST_PP_NOR(X,X)

/** <P>Obsolete. Use BOOST_PP_NOT().</P> */
#define BOOST_PREPROCESSOR_NOT(X) BOOST_PP_NOT(X)
#endif
