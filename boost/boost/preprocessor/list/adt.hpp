#ifndef BOOST_PREPROCESSOR_LIST_ADT_HPP
#define BOOST_PREPROCESSOR_LIST_ADT_HPP

/* Copyright (C) 2001
 * Housemarque Oy
 * http://www.housemarque.com
 *
 * Permission to copy, use, modify, sell and distribute this software is
 * granted provided this copyright notice appears in all copies. This
 * software is provided "as is" without express or implied warranty, and
 * with no claim as to its suitability for any purpose.
 *
 * See http://www.boost.org for most recent version.
 */

/** <P>This header defines the fundamental list operations.</P>

<P>NOTE: The internal representation of lists is hidden. Although there
aren't compelling reasons to change the representation, you should avoid
writing code that depends on the internal representation details.</P>
*/

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/logical/not.hpp>

/** <P>List constructor.</P>

<P>Lists are build using list constructors BOOST_PP_LIST_NIL and
BOOST_PP_LIST_CONS(). For example,</P>

<PRE>
  BOOST_PP_LIST_CONS(1,
  BOOST_PP_LIST_CONS(2,
  BOOST_PP_LIST_CONS(3,
  BOOST_PP_LIST_CONS(4,
  BOOST_PP_LIST_CONS(5,
  BOOST_PP_LIST_NIL)))))
</PRE>

<P>Short lists can also be build from tuples:</P>

<PRE>
  BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5))
</PRE>

<P>Both of the above lists contain 5 elements: 1, 2, 3, 4 and 5.</P>
*/
#define BOOST_PP_LIST_CONS(H,T) (H,T,1)

/** <P>List nil constructor.</P>

<H3>See</H3>
<UL>
  <LI>BOOST_PP_LIST_CONS()
</UL>
*/
#define BOOST_PP_LIST_NIL (_,_,0)

/** <P>Expands to 1 if the list is not nil and 0 otherwise.</P>

<H3>See</H3>
<UL>
  <LI>BOOST_PP_LIST_IS_NIL()
</UL>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE_ELEM(3,2,L)
#else
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE3_ELEM2 L
#endif

/** <P>Expands to 1 if the list is nil and 0 otherwise.</P>

<H3>See</H3>
<UL>
  <LI>BOOST_PP_LIST_IS_CONS()
</UL>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE_ELEM(3,2,L))
#else
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE3_ELEM2 L)
#endif

/** <P>Expands to the first element of the list. The list must not be nil.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_LIST_FIRST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
</PRE>

<P>expands to 1.</P>

<H3>See</H3>
<UL>
  <LI>BOOST_PP_LIST_REST()
</UL>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE_ELEM(3,0,L)
#else
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE3_ELEM0 L
#endif

/** <P>Expands to a list of all but the first element of the list. The list must not be nil.</P>

<P>For example,</P>

<PRE>
  BOOST_PP_LIST_REST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
</PRE>

<P>expands to a list containing 2, 3, 4 and 5.</P>

<H3>See</H3>
<UL>
  <LI>BOOST_PP_LIST_FIRST()
</UL>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE_ELEM(3,1,L)
#else
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE3_ELEM1 L
#endif
#endif
