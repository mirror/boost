#ifndef BOOST_PREPROCESSOR_EMPTY_HPP
#define BOOST_PREPROCESSOR_EMPTY_HPP

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

<a href="../../../../boost/preprocessor/empty.hpp">Click here to see the header.</a>
*/

//! Expands to nothing. Used with BOOST_PREPROCESSOR_IF() and as an unused parameter.
/*!
Example usage as the implementation of BOOST_PREPROCESSOR_COMMA_IF(C):

<PRE>\verbatim
  #define BOOST_PREPROCESSOR_COMMA_IF(C)\
    BOOST_PREPROCESSOR_IF(C,BOOST_PREPROCESSOR_COMMA,BOOST_PREPROCESSOR_EMPTY)()
\endverbatim</PRE>

Example usage as an unused macro parameter:

<PRE>\verbatim
  #define BOOST_PREPROCESSOR_DEF(CV)\
    template<class base>            \
    CV typename implement_subscript_using_begin_subscript<base>::value_type&\
      implement_subscript_using_begin_subscript<base>::operator[]\
      ( index_type                  \
          i                         \
      ) CV                          \
    { return base::begin()[i];      \
    }

  BOOST_PREPROCESSOR_DEF(BOOST_PREPROCESSOR_EMPTY())
  BOOST_PREPROCESSOR_DEF(const)
  #undef BOOST_PREPROCESSOR_DEF
\endverbatim</PRE>

The above expands to:

<PRE>\verbatim
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
\endverbatim</PRE>

In case you wonder, the above code is part of a generalized layer for
implementing the subscripting operators of a random access container.
*/
#define BOOST_PREPROCESSOR_EMPTY()
#endif
