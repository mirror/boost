#ifndef BOOST_PREPROCESSOR_ENUM_PARAMS_HPP
#define BOOST_PREPROCESSOR_ENUM_PARAMS_HPP

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

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/enum.hpp>

/** <p>Generates a comma separated list of parameters.</p>

<p>In other words, expands to the sequence:</p>

<pre>
  BOOST_PP_CAT(P,0), BOOST_PP_CAT(P,1), ..., BOOST_PP_CAT(P,BOOST_PP_DEC(N))
</pre>

<h3>Uses</h3>
<ul>
  <li>BOOST_PP_REPEAT()</li>
</ul>
*/
#define BOOST_PP_ENUM_PARAMS(N,P) BOOST_PP_ENUM(N,BOOST_PP_ENUM_PARAMS_F,P)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_ENUM_PARAMS_F(I,P) BOOST_PP_CAT(P,I)
#endif

/** <p>Obsolete. Use BOOST_PP_ENUM_PARAMS().</p> */
#define BOOST_PREPROCESSOR_ENUM_PARAMS(N,P) BOOST_PP_ENUM_PARAMS(N,P)
#endif
