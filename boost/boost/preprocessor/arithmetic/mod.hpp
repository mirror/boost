#ifndef BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP
#define BOOST_PREPROCESSOR_ARITHMETIC_MOD_HPP

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

<a href="../../../../boost/preprocessor/arithmetic/mod.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#  include <boost/preprocessor/arithmetic/sub.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#  include <boost/preprocessor/comparison/less_equal.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_TUPLE_HPP
#  include <boost/preprocessor/tuple.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_WHILE_HPP
#  include <boost/preprocessor/while.hpp>
#endif

//! Expands to the remainder of X and Y.
#define BOOST_PREPROCESSOR_MOD(X,Y) BOOST_PREPROCESSOR_MOD_I(0,X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PREPROCESSOR_MOD_I(I,X,Y) BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,BOOST_PREPROCESSOR_WHILE##I(BOOST_PREPROCESSOR_MOD_C,BOOST_PREPROCESSOR_MOD_F,(X,Y)))
#define BOOST_PREPROCESSOR_MOD_C(I,P) BOOST_PREPROCESSOR_LESS_EQUAL_I(I,BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,P),BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,P))
#define BOOST_PREPROCESSOR_MOD_F(I,P) (BOOST_PREPROCESSOR_SUB_I(I,BOOST_PREPROCESSOR_TUPLE_ELEM(2,0,P),BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,P)),BOOST_PREPROCESSOR_TUPLE_ELEM(2,1,P))
#endif /* DOXYGEN_SHOULD_SKIP_THIS */
#endif
