#ifndef BOOST_PREPROCESSOR_IF_HPP
#define BOOST_PREPROCESSOR_IF_HPP

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

#include <boost/preprocessor/logical/bool.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

/** <p>Expands to <code>T</code> if <code>C != 0</code> and <code>E</code> if
<code>C == 0</code>.</p>

<p>BOOST_PP_IF() enables convenient generation of lists using
BOOST_PP_REPEAT().</p>

<h3>Test</h3>
<ul>
  <li><a href="../../test/preprocessor_test.cpp">preprocessor_test.cpp</a></li>
</ul>
*/
#define BOOST_PP_IF(C,T,E) BOOST_PP_IF_BOOL(BOOST_PP_BOOL(C))(E,T)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_IF_BOOL(C) BOOST_PP_IF_BOOL_DELAY(C)
#define BOOST_PP_IF_BOOL_DELAY(C) BOOST_PP_TUPLE2_ELEM##C
#endif

/** <p>Obsolete. Use BOOST_PP_IF().</p> */
#define BOOST_PREPROCESSOR_IF(C,T,E) BOOST_PP_IF(C,T,E)
#endif
