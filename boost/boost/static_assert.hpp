//  (C) Copyright John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.

/*
 Revision history:
 	02 August 2000
 		Initial version.
*/

#ifndef BOOST_STATIC_ASSERT_HPP
#define BOOST_STATIC_ASSERT_HPP

#include <boost/config.hpp>

#ifdef __BORLANDC__
//
// workaround for buggy integral-constant expression support:
#define BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS
#endif

namespace boost{

template <bool> struct STATIC_ASSERTION_FAILURE;

template <> struct STATIC_ASSERTION_FAILURE<true>{};

template<int> struct static_assert_test{};

}

//
// Implicit instantiation requires that all member declarations be
// instantiated, but that the definitions are *not* instantiated.
//
// It's not particularly clear how this applies to enum's or typedefs;
// both are described as declarations [7.1.3] and [7.2] in the standard,
// however some compilers use "delayed evaluation" of one or more of
// these when implicitly instantiating templates.  We use typedef declarations
// by default, but try defining BOOST_USE_ENUM_STATIC_ASSERT if the enum
// version gets better results from your compiler...
//
// Implementation:
// Both of these versions rely on sizeof(incomplete_type) generating an error
// message containing the name of the incomplete type.  We use
// "STATIC_ASSERTION_FAILURE" as the type name here to generate
// an eye catching error message.  The result of the sizeof expression is either
// used as an enum initialiser, or as a template argument depending which version
// is in use...
//
#ifndef BOOST_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS
#ifndef BOOST_MSVC
#define BOOST_STATIC_ASSERT( B ) \
   typedef ::boost::static_assert_test<\
      sizeof(::boost::STATIC_ASSERTION_FAILURE< ( B ) >)>\
         BOOST_ASSERT_JOIN(boost_static_assert_typedef_, __LINE__)
#else
// __LINE__ macro broken when -ZI is used see Q199057
// fortunately MSVC ignores duplicate typedef's:
#define BOOST_STATIC_ASSERT( B ) \
   typedef ::boost::static_assert_test<\
      sizeof(::boost::STATIC_ASSERTION_FAILURE< ( B ) >)\
      > boost_static_assert_typedef_
#endif
#else
// alternative enum based implementation:
#define BOOST_STATIC_ASSERT( B ) \
   enum { BOOST_ASSERT_JOIN(boost_static_assert_enum_, __LINE__) \
      = sizeof(::boost::STATIC_ASSERTION_FAILURE< ( B ) >) }
#endif

//
// The following piece of macro magic joins the two 
// arguments together, even when one of the arguments is
// itself a macro (see 16.3.1 in C++ standard).  The key
// is that macro expantion of macro arguments does not
// occur in BOOST_DO_ASSERT_JOIN but does in BOOST_ASSERT_JOIN
// provided it is called from within another macro.
#define BOOST_ASSERT_JOIN( X, Y ) BOOST_DO_ASSERT_JOIN( X, Y )
#define BOOST_DO_ASSERT_JOIN( X, Y ) X##Y

#endif // BOOST_STATIC_ASSERT_HPP



