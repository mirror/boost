#ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#define BOOST_PREPROCESSOR_LOGICAL_OR_HPP

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

<a href="../../../../boost/preprocessor/logical/or.hpp">Click here to see the header.</a>
*/

#ifndef BOOST_PREPROCESSOR_LOGICAL_NOR_HPP
#  include <boost/preprocessor/logical/nor.hpp>
#endif
#ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#  include <boost/preprocessor/logical/not.hpp>
#endif

//! Expands to the logical OR of the operands. 
#define BOOST_PREPROCESSOR_OR(X,Y) BOOST_PREPROCESSOR_NOT(BOOST_PREPROCESSOR_NOR(X,Y))
#endif
