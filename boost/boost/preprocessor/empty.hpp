#ifndef BOOST_PREPROCESSOR_EMPTY_HPP
#define BOOST_PREPROCESSOR_EMPTY_HPP

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

/** <P>Expands to nothing. Used with BOOST_PP_IF() and as an unused parameter.</P>

<P>Example usage as the implementation of BOOST_PP_COMMA_IF(C):</P>

<PRE>
  #define BOOST_PP_COMMA_IF(C)\
    BOOST_PP_IF(C,BOOST_PP_COMMA,BOOST_PP_EMPTY)()
</PRE>

<P>Example usage as an unused macro parameter:</P>

<PRE>
  #define BOOST_PP_DEF(CV)\
    template<class base>\
    CV() typename implement_subscript_using_begin_subscript<base>::value_type&\
      implement_subscript_using_begin_subscript<base>::operator[]\
      ( index_type\
          i\
      ) CV()\
    { return base::begin()[i];\
    }

  BOOST_PP_DEF(BOOST_PP_EMPTY)
  BOOST_PP_DEF(const BOOST_PP_EMPTY)
  #undef BOOST_PP_DEF
</PRE>

<P>The above expands to:</P>

<PRE>
  template<class base>
  typename implement_subscript_using_begin_subscript<base>::value_type&
    implement_subscript_using_begin_subscript<base>::operator[]
    ( index_type
        i
    )
  { return base::begin()[i];
  }

  template<class base>
  const typename implement_subscript_using_begin_subscript<base>::value_type&
    implement_subscript_using_begin_subscript<base>::operator[]
    ( index_type
        i
    ) const
  { return base::begin()[i];
  }
</PRE>

<P>In case you wonder, the above code is part of a generalized layer for
implementing the subscripting operators of a random access container.</P>
*/
#define BOOST_PP_EMPTY()

/** <P>Obsolete. Use BOOST_PP_EMPTY().</P> */
#define BOOST_PREPROCESSOR_EMPTY()
#endif
