#ifndef BOOST_PREPROCESSOR_LIST_ADT_HPP
#define BOOST_PREPROCESSOR_LIST_ADT_HPP

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

<a href="../../../../boost/preprocessor/list/adt.hpp">Click here to see the header.</a>

This header defines the fundamental list operations.

NOTE: The internal representation of lists is hidden. Although there aren't
compelling reasons to change the representation, you should avoid writing
code that depends on the internal representation details.
*/

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/logical/not.hpp>

//! List constructor.
/*!
Lists are build using list constructors BOOST_PP_LIST_NIL and
BOOST_PP_LIST_CONS(). For example,

<PRE>\verbatim
  BOOST_PP_LIST_CONS(1,
  BOOST_PP_LIST_CONS(2,
  BOOST_PP_LIST_CONS(3,
  BOOST_PP_LIST_CONS(4,
  BOOST_PP_LIST_CONS(5,
  BOOST_PP_LIST_NIL)))))
\endverbatim</PRE>

Short lists can also be build from tuples:

<PRE>\verbatim
  BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5))
\endverbatim</PRE>

Both of the above lists contain 5 elements: 1, 2, 3, 4 and 5.
*/
#define BOOST_PP_LIST_CONS(H,T) (H,T,1)

//! List nil constructor.
/*!
See BOOST_PP_LIST_CONS().
*/
#define BOOST_PP_LIST_NIL (_,_,0)

//! Expands to 1 if the list is not nil and 0 otherwise.
/*!
See BOOST_PP_LIST_IS_NIL().
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE_ELEM(3,2,L)
#else
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE3_ELEM2 L
#endif

//! Expands to 1 if the list is nil and 0 otherwise.
/*!
See BOOST_PP_LIST_IS_CONS().
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE_ELEM(3,2,L))
#else
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE3_ELEM2 L)
#endif

//! Expands to the first element of the list. The list must not be nil.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_FIRST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
\endverbatim</PRE>

expands to 1.

See BOOST_PP_LIST_REST().
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE_ELEM(3,0,L)
#else
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE3_ELEM0 L
#endif

//! Expands to a list of all but the first element of the list. The list must not be nil.
/*!
For example,

<PRE>\verbatim
  BOOST_PP_LIST_REST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
\endverbatim</PRE>

expands to a list containing 2, 3, 4 and 5.

See BOOST_PP_LIST_FIRST().
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE_ELEM(3,1,L)
#else
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE3_ELEM1 L
#endif
#endif
