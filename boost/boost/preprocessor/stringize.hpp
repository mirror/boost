#ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
#define BOOST_PREPROCESSOR_STRINGIZE_HPP

// Copyright (C) 2001
// Housemarque Oy
// http://www.housemarque.com
//
// Permission to copy, use, modify, sell and distribute this software is
// granted provided this copyright notice appears in all copies. This
// software is provided "as is" without express or implied warranty, and
// with no claim as to its suitability for any purpose.

// See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/stringize.hpp">Click here to see the header.</a>
*/

//! Delays the stringization of E.
/*!
Example:

<PRE>\verbatim
#define NOTE(STR)\
  message(__FILE__ "(" BOOST_PREPROCESSOR_STRINGIZE(__LINE__) ") : " STR)

// ...

#pragma NOTE("TBD!")
\endverbatim</PRE>

The above expands to:

<PRE>\verbatim
  #pragma message("examples.cpp" "(" "20" ") : " "TBD!")
\endverbatim</PRE>

The use of BOOST_PREPROCESSOR_STRINGIZE() above lets the preprocessor expand
the __LINE__ before stringizing it. If # would be used directly, the code
would expand to:

<PRE>\verbatim
  #pragma message("examples.cpp" "(" "__LINE__" ") : " "TBD!")
\endverbatim</PRE>
*/
#define BOOST_PREPROCESSOR_STRINGIZE(E) BOOST_PREPROCESSOR_STRINGIZE_DELAY(E)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_STRINGIZE_DELAY(E) #E
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
