#ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP

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

<a href="../../../../boost/preprocessor/arithmetic/add.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_INC_HPP
#  include <boost/preprocessor/inc.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_TUPLE_HPP
#  include <boost/preprocessor/tuple.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_WHILE_HPP
#  include <boost/preprocessor/while.hpp>
#endif

//! Expands to the sum of X and Y.
#define BOOST_PREPROCESSOR_ADD(X,Y) BOOST_PREPROCESSOR_ADD_I(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_ADD_I(I,X,Y) BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,BOOST_PREPROCESSOR_WHILE##I(BOOST_PREPROCESSOR_ADD_C,BOOST_PREPROCESSOR_ADD_F,(X,Y)))
#define BOOST_PREPROCESSOR_ADD_C(I,P) BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,P)
#define BOOST_PREPROCESSOR_ADD_F(I,P) (BOOST_PREPROCESSOR_INC(BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,P)),BOOST_PREPROCESSOR_DEC(BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,P)))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
