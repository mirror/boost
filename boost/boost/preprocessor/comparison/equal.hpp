#ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#define BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP

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

<a href="../../../../boost/preprocessor/comparison/equal.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#  include <boost/preprocessor/arithmetic/add.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#  include <boost/preprocessor/arithmetic/sub.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#  include <boost/preprocessor/logical/not.hpp>
#endif

//! Expands to 1 if X==Y and 0 otherwise.
#define BOOST_PREPROCESSOR_EQUAL(X,Y) BOOST_PREPROCESSOR_NOT(BOOST_PREPROCESSOR_ADD(BOOST_PREPROCESSOR_SUB(X,Y),BOOST_PREPROCESSOR_SUB(Y,X)))
#endif
