#ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP

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

<a href="../../../../boost/preprocessor/arithmetic/div.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#  include <boost/preprocessor/arithmetic/sub.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#  include <boost/preprocessor/comparison/less_equal.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_INC_HPP
#  include <boost/preprocessor/inc.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_TUPLE_HPP
#  include <boost/preprocessor/tuple.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_WHILE_HPP
#  include <boost/preprocessor/while.hpp>
#endif

//! Expands to the quotient of X and Y.
#define BOOST_PREPROCESSOR_DIV(X,Y) BOOST_PREPROCESSOR_DIV_I(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_DIV_I(I,X,Y) BOOST_PREPROCESSOR_TUPLE_ELEM(3,0,BOOST_PREPROCESSOR_WHILE##I(BOOST_PREPROCESSOR_DIV_C,BOOST_PREPROCESSOR_DIV_F,(0,X,Y)))
#define BOOST_PREPROCESSOR_DIV_C(I,P) BOOST_PREPROCESSOR_LESS_EQUAL_I(I,BOOST_PREPROCESSOR_TUPLE_ELEM(3,2,P),BOOST_PREPROCESSOR_TUPLE_ELEM(3,1,P))
#define BOOST_PREPROCESSOR_DIV_F(I,P) (BOOST_PREPROCESSOR_INC(BOOST_PREPROCESSOR_TUPLE_ELEM(3,0,P)),BOOST_PREPROCESSOR_SUB_I(I,BOOST_PREPROCESSOR_TUPLE_ELEM(3,1,P),BOOST_PREPROCESSOR_TUPLE_ELEM(3,2,P)),BOOST_PREPROCESSOR_TUPLE_ELEM(3,2,P))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
