#ifndef BOOST_PREPROCESSOR_IF_HPP
#define BOOST_PREPROCESSOR_IF_HPP

//  Copyright (C) 2001
//  Housemarque, Inc.
//  http://www.housemarque.com
//  
//  Permission to copy, use, modify, sell and distribute this software is
//  granted provided this copyright notice appears in all copies. This
//  software is provided "as is" without express or implied warranty, and
//  with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version.

/*! \file

<a href="../../../../boost/preprocessor/if.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_LOGICAL_BOOL_HPP
#  include <boost/preprocessor/logical/bool.hpp>
#endif

//! Expands to T if C != 0 and E if C == 0.
/*!
BOOST_PREPROCESSOR_IF() enables convenient generation of lists using
BOOST_PREPROCESSOR_REPEAT().
*/
#define BOOST_PREPROCESSOR_IF(C,T,E) BOOST_PREPROCESSOR_IF_BOOL(BOOST_PREPROCESSOR_BOOL(C),T,E)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_IF_BOOL(C,T,E) BOOST_PREPROCESSOR_IF_BOOL_DELAY(C,T,E)
#define BOOST_PREPROCESSOR_IF_BOOL_DELAY(C,T,E) BOOST_PREPROCESSOR_IF_BOOL##C(T,E)
#define BOOST_PREPROCESSOR_IF_BOOL0(T,E) E
#define BOOST_PREPROCESSOR_IF_BOOL1(T,E) T
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
