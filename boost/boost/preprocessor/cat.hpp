#ifndef BOOST_PREPROCESSOR_CAT_HPP
#define BOOST_PREPROCESSOR_CAT_HPP

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

/** <P>Delays the catenation of X and Y.</P>

<P>For example,</P>

<PRE>
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
</PRE>

<P>expands to:</P>

<PRE>
  enum
  { static_check_152 = (sizeof(int) <= sizeof(long)) ? 1 : -1
  };
  typedef char
    static_assert_152
    [ static_check_152
    ];
</PRE>

<P>Using BOOST_PP_CAT() above lets the PP expand the __LINE__. If the above
code would use the ## operator directly then __LINE__ would not be expanded and
the above would expand to:</P>

<PRE>
  enum
  { static_check___LINE__ = (sizeof(int) <= sizeof(long)) ? 1 : -1
  };
  typedef char
    static_assert___LINE__
    [ static_check___LINE__
    ];
</PRE>
*/
#define BOOST_PP_CAT(X,Y) BOOST_PP_CAT_DELAY(X,Y)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#define BOOST_PP_CAT_DELAY(X,Y) BOOST_PP_DO_CAT(X,Y)
#define BOOST_PP_DO_CAT(X,Y) X##Y
#endif

/** <P>Obsolete. Use BOOST_PP_CAT().</P> */
#define BOOST_PREPROCESSOR_CAT(X,Y) BOOST_PP_CAT(X,Y)
#endif
