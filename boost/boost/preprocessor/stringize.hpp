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

/** <P>Delays the stringization of X.</P>

<P>For example,</P>

<PRE>
  #define NOTE(STR)\
    message(__FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) ") : " STR)

  // ...

  #pragma NOTE("TBD!")
</PRE>

<P>expands to:</P>

<PRE>
  #pragma message("examples.cpp" "(" "20" ") : " "TBD!")
</PRE>

<P>The use of BOOST_PP_STRINGIZE() above lets the PP expand the __LINE__
before stringizing it. If # would be used directly, the code would
expand to:</P>

<PRE>
  #pragma message("examples.cpp" "(" "__LINE__" ") : " "TBD!")
</PRE>
*/
#define BOOST_PP_STRINGIZE(X) BOOST_PP_STRINGIZE_DELAY(X)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_STRINGIZE_DELAY(X) BOOST_PP_DO_STRINGIZE(X)
#define BOOST_PP_DO_STRINGIZE(X) #X
#endif

/** <P>Obsolete. Use BOOST_PP_STRINGIZE().</P> */
#define BOOST_PREPROCESSOR_STRINGIZE(E) BOOST_PP_STRINGIZE(E)
#endif
