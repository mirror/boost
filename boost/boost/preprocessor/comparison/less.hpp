#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_HPP
#define BOOST_PREPROCESSOR_COMPARISON_LESS_HPP

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

<a href="../../../../boost/preprocessor/comparison/less.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_COMPARISON_EQUAL_HPP
#  include <boost/preprocessor/comparison/equal.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_COMPARISON_LESS_EQUAL_HPP
#  include <boost/preprocessor/comparison/less_equal.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_IF_HPP
#  include <boost/preprocessor/if.hpp>
#endif

//! Expands to 1 if X<Y and 0 otherwise.
#define BOOST_PREPROCESSOR_LESS(X,Y) BOOST_PREPROCESSOR_IF(BOOST_PREPROCESSOR_EQUAL(X,Y),0,BOOST_PREPROCESSOR_LESS_EQUAL(X,Y))
#endif
