#ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
#define BOOST_PREPROCESSOR_STRINGIZE_HPP

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

/** \file

<a href="../../../../boost/preprocessor/stringize.hpp">Click here to see the header.</a>
*/

/** Delays the stringization of X.

For example,

<PRE>\verbatim
#define NOTE(STR)\
  message(__FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) ") : " STR)

// ...

#pragma NOTE("TBD!")
\endverbatim</PRE>

expands to:

<PRE>\verbatim
  #pragma message("examples.cpp" "(" "20" ") : " "TBD!")
\endverbatim</PRE>

The use of BOOST_PP_STRINGIZE() above lets the PP expand the __LINE__
before stringizing it. If # would be used directly, the code would
expand to:

<PRE>\verbatim
  #pragma message("examples.cpp" "(" "__LINE__" ") : " "TBD!")
\endverbatim</PRE>
*/
#define BOOST_PP_STRINGIZE(X) BOOST_PP_STRINGIZE_DELAY(X)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_STRINGIZE_DELAY(X) BOOST_PP_DO_STRINGIZE(X)
#define BOOST_PP_DO_STRINGIZE(X) #X
#endif

/** Obsolete. Use BOOST_PP_STRINGIZE(). */
#define BOOST_PREPROCESSOR_STRINGIZE(E) BOOST_PP_STRINGIZE(E)
#endif
