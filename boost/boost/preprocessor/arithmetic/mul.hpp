#ifndef BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP

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

<a href="../../../../boost/preprocessor/arithmetic/mul.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#  include <boost/preprocessor/arithmetic/add.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_TUPLE_HPP
#  include <boost/preprocessor/tuple.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_WHILE_HPP
#  include <boost/preprocessor/while.hpp>
#endif

//! Expands to the product of X and Y.
#define BOOST_PREPROCESSOR_MUL(X,Y) BOOST_PREPROCESSOR_MUL_I(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_MUL_I(I,X,Y) BOOST_PREPROCESSOR_TUPLE_ELEM(3,0,BOOST_PREPROCESSOR_WHILE##I(BOOST_PREPROCESSOR_MUL_C,BOOST_PREPROCESSOR_MUL_F,(0,X,Y)))
#define BOOST_PREPROCESSOR_MUL_C(I,P) BOOST_PREPROCESSOR_TUPLE_ELEM(3,2,P)
#define BOOST_PREPROCESSOR_MUL_F(I,P) (BOOST_PREPROCESSOR_ADD_I(I,BOOST_PREPROCESSOR_TUPLE_ELEM(3,0,P),BOOST_PREPROCESSOR_TUPLE_ELEM(3,1,P)),BOOST_PREPROCESSOR_TUPLE_ELEM(3,1,P),BOOST_PREPROCESSOR_DEC(BOOST_PREPROCESSOR_TUPLE_ELEM(3,2,P)))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
