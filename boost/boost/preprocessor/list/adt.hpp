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

/** <p>This header defines the fundamental list operations.</p>

<h3>Note</h3>
<ul>
  <li>The internal representation of lists is hidden. Although there aren't
      compelling reasons to change the representation, you should avoid
      writing code that depends on the internal representation details.</li>
</ul>
*/

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/logical/not.hpp>

/** <p>List constructor.</p>

<p>Lists are build using list constructors BOOST_PP_LIST_NIL and
BOOST_PP_LIST_CONS(). For example,</p>

<pre>
  BOOST_PP_LIST_CONS(1,
  BOOST_PP_LIST_CONS(2,
  BOOST_PP_LIST_CONS(3,
  BOOST_PP_LIST_CONS(4,
  BOOST_PP_LIST_CONS(5,
  BOOST_PP_LIST_NIL)))))
</pre>

<p>Short lists can also be build from tuples:</p>

<pre>
  BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5))
</pre>

<p>Both of the above lists contain 5 elements: 1, 2, 3, 4 and 5.</p>

<p>Longer lists can be built with the help of BOOST_PP_LIST_APPEND().</p>
*/
#define BOOST_PP_LIST_CONS(H,T) (H,T,1)

/** <p>List nil constructor.</p> */
#define BOOST_PP_LIST_NIL (_,_,0)

/** <p>Expands to 1 if the list is not nil and 0 otherwise.</p> */
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE_ELEM(3,2,L)
#else
#  define BOOST_PP_LIST_IS_CONS(L) BOOST_PP_TUPLE3_ELEM2 L
#endif

/** <p>Expands to 1 if the list is nil and 0 otherwise.</p> */
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE_ELEM(3,2,L))
#else
#  define BOOST_PP_LIST_IS_NIL(L) BOOST_PP_NOT(BOOST_PP_TUPLE3_ELEM2 L)
#endif

/** <p>Expands to the first element of the list. The list must not be nil.</p>

<p>For example,</p>

<pre>
  BOOST_PP_LIST_FIRST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
</pre>

<p>expands to 1.</p>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE_ELEM(3,0,L)
#else
#  define BOOST_PP_LIST_FIRST(L) BOOST_PP_TUPLE3_ELEM0 L
#endif

/** <p>Expands to a list of all but the first element of the list.</p>

<p>The list must not be nil.</p>

<p>For example,</p>

<pre>
  BOOST_PP_LIST_REST(BOOST_PP_TUPLE_TO_LIST(5,(1,2,3,4,5)))
</pre>

<p>expands to the same as:</p>

<pre>
  BOOST_PP_TUPLE_TO_LIST(4,(2,3,4,5))
</pre>
*/
#if !defined(BOOST_NO_COMPILER_CONFIG) && defined(__MWERKS__) && __MWERKS__ <= 0x2406
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE_ELEM(3,1,L)
#else
#  define BOOST_PP_LIST_REST(L) BOOST_PP_TUPLE3_ELEM1 L
#endif
#endif
