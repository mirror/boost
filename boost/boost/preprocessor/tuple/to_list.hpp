#ifndef BOOST_PREPROCESSOR_TUPLE_TO_LIST_HPP
#define BOOST_PREPROCESSOR_TUPLE_TO_LIST_HPP

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

<a href="../../../../boost/preprocessor/tuple/to_list.hpp">Click here to see the header.</a>
*/

#include <boost/preprocessor/list/adt.hpp>

//! Converts a tuple to a list.
/*!
See BOOST_PP_LIST_CONS() for an example.

See BOOST_PP_LIMIT_TUPLE.
*/
#define BOOST_PP_TUPLE_TO_LIST(N,T) BOOST_PP_TUPLE_TO_LIST_DELAY(N,T)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_TUPLE_TO_LIST_DELAY(N,T) BOOST_PP_TUPLE##N##_TO_LIST T
#define BOOST_PP_TUPLE0_TO_LIST() BOOST_PP_LIST_NIL
#define BOOST_PP_TUPLE1_TO_LIST(A) BOOST_PP_LIST_CONS(A,BOOST_PP_LIST_NIL)
#define BOOST_PP_TUPLE2_TO_LIST(A,B) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE1_TO_LIST(B))
#define BOOST_PP_TUPLE3_TO_LIST(A,B,C) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE2_TO_LIST(B,C))
#define BOOST_PP_TUPLE4_TO_LIST(A,B,C,D) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE3_TO_LIST(B,C,D))
#define BOOST_PP_TUPLE5_TO_LIST(A,B,C,D,E) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE4_TO_LIST(B,C,D,E))
#define BOOST_PP_TUPLE6_TO_LIST(A,B,C,D,E,F) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE5_TO_LIST(B,C,D,E,F))
#define BOOST_PP_TUPLE7_TO_LIST(A,B,C,D,E,F,G) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE6_TO_LIST(B,C,D,E,F,G))
#define BOOST_PP_TUPLE8_TO_LIST(A,B,C,D,E,F,G,H) BOOST_PP_LIST_CONS(A,BOOST_PP_TUPLE7_TO_LIST(B,C,D,E,F,G,H))
#endif
#endif
