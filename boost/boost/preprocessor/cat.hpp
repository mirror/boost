#ifndef BOOST_PREPROCESSOR_CAT_HPP
#define BOOST_PREPROCESSOR_CAT_HPP

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

<a href="../../../../boost/preprocessor/cat.hpp">Click here to see the header.</a>
*/

//! Delays the catenation of L and R.
/*!
Example:

<PRE>\verbatim
  #define STATIC_ASSERT(EXPR)\
    enum\
    { BOOST_PP_CAT(static_check_,__LINE__) = (EXPR) ? 1 : -1\
    };\
    typedef char\
      BOOST_PP_CAT(static_assert_,__LINE__)\
      [ BOOST_PP_CAT(static_check_,__LINE__)\
      ]

  // ...

  STATIC_ASSERT(sizeof(int) <= sizeof(long));
\endverbatim</PRE>

The above expands to:

<PRE>\verbatim
  enum
  { static_check_152 = (sizeof(int) <= sizeof(long)) ? 1 : -1
  };
  typedef char
    static_assert_152
    [ static_check_152
    ];
\endverbatim</PRE>

Using BOOST_PP_CAT() above lets the PP expand the __LINE__.
If the above code would use the ## operator directly then __LINE__ would not be
expanded and the above would expand to:

<PRE>\verbatim
  enum
  { static_check___LINE__ = (sizeof(int) <= sizeof(long)) ? 1 : -1
  };
  typedef char
    static_assert___LINE__
    [ static_check___LINE__
    ];
\endverbatim</PRE>
*/
#define BOOST_PP_CAT(L,R) BOOST_PP_CAT_DELAY(L,R)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_CAT_DELAY(L,R) L##R
#endif

//! Obsolete. Use BOOST_PP_CAT().
#define BOOST_PREPROCESSOR_CAT(L,R) BOOST_PP_CAT(L,R)
#endif
