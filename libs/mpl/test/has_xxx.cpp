
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Daniel Walker 2007
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/test.hpp>

BOOST_MPL_HAS_XXX_TRAIT_DEF(xxx)
BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(has_xxx0, xxx, 0, false)
BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(has_xxx1, xxx, 1, false)
BOOST_MPL_HAS_XXX_TEMPLATE_NAMED_DEF(has_xxx2, xxx, 2, false)
BOOST_MPL_HAS_XXX_TEMPLATE_DEF(yyy0, 0)
BOOST_MPL_HAS_XXX_TEMPLATE_DEF(yyy1, 1)
BOOST_MPL_HAS_XXX_TEMPLATE_DEF(yyy2, 2)

struct a1 {};
struct a2 { void xxx(); };
struct a3 { int xxx; };
struct a4 { static int xxx(); };
struct a5 { template< typename T > struct xxx {}; };

struct b1 { typedef int xxx; };
struct b2 { struct xxx; };
struct b3 { typedef int& xxx; };
struct b4 { typedef int* xxx; };
struct b5 { typedef int xxx[10]; };
struct b6 { typedef void (*xxx)(); };
struct b7 { typedef void (xxx)(); };

struct c0 { template< typename T0 = int > struct xxx {}; };
struct c1 { template< typename T1 > struct xxx {}; };
struct c2 { template< typename T1, typename T2 > struct xxx {}; };
struct c3 { template< typename T0 = int > struct yyy0 {}; };
struct c4 { template< typename T1 > struct yyy1 {}; };
struct c5 { template< typename T1, typename T2 > struct yyy2 {}; };

template< typename T > struct outer;
template< typename T > struct inner { typedef typename T::type type; };

// agurt, 15/aug/04: make sure MWCW passes the test in presence of the following
// template
template< typename T > struct xxx;


MPL_TEST_CASE()
{
    MPL_ASSERT_NOT(( has_xxx<int> ));
    MPL_ASSERT_NOT(( has_xxx0< int > ));
    MPL_ASSERT_NOT(( has_xxx1< int, int > ));
    MPL_ASSERT_NOT(( has_xxx2< int, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< int > ));
    MPL_ASSERT_NOT(( has_yyy1< int, int > ));
    MPL_ASSERT_NOT(( has_yyy2< int, int, int > ));

#if !BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
    MPL_ASSERT_NOT(( has_xxx<int&> ));
    MPL_ASSERT_NOT(( has_xxx0< int& > ));
    MPL_ASSERT_NOT(( has_xxx1< int&, int > ));
    MPL_ASSERT_NOT(( has_xxx2< int&, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< int& > ));
    MPL_ASSERT_NOT(( has_yyy1< int&, int > ));
    MPL_ASSERT_NOT(( has_yyy2< int&, int, int > ));

    MPL_ASSERT_NOT(( has_xxx<int*> ));
    MPL_ASSERT_NOT(( has_xxx0< int* > ));
    MPL_ASSERT_NOT(( has_xxx1< int*, int > ));
    MPL_ASSERT_NOT(( has_xxx2< int*, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< int* > ));
    MPL_ASSERT_NOT(( has_yyy1< int*, int > ));
    MPL_ASSERT_NOT(( has_yyy2< int*, int, int > ));

    MPL_ASSERT_NOT(( has_xxx<int[]> ));
    MPL_ASSERT_NOT(( has_xxx0< int[] > ));
    MPL_ASSERT_NOT(( has_xxx1< int[], int > ));
    MPL_ASSERT_NOT(( has_xxx2< int[], int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< int[] > ));
    MPL_ASSERT_NOT(( has_yyy1< int[], int > ));
    MPL_ASSERT_NOT(( has_yyy2< int[], int, int > ));

    MPL_ASSERT_NOT(( has_xxx<int (*)()> ));
    MPL_ASSERT_NOT(( has_xxx0< int (*)() > ));
    MPL_ASSERT_NOT(( has_xxx1< int (*)(), int > ));
    MPL_ASSERT_NOT(( has_xxx2< int (*)(), int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< int (*)() > ));
    MPL_ASSERT_NOT(( has_yyy1< int (*)(), int > ));
    MPL_ASSERT_NOT(( has_yyy2< int (*)(), int, int > ));

    MPL_ASSERT_NOT(( has_xxx<a2> ));
    MPL_ASSERT_NOT(( has_xxx0< a2 > ));
    MPL_ASSERT_NOT(( has_xxx1< a2, int > ));
    MPL_ASSERT_NOT(( has_xxx2< a2, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< a2 > ));
    MPL_ASSERT_NOT(( has_yyy1< a2, int > ));
    MPL_ASSERT_NOT(( has_yyy2< a2, int, int > ));

    MPL_ASSERT_NOT(( has_xxx<a3> ));
    MPL_ASSERT_NOT(( has_xxx0< a3 > ));
    MPL_ASSERT_NOT(( has_xxx1< a3, int > ));
    MPL_ASSERT_NOT(( has_xxx2< a3, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< a3 > ));
    MPL_ASSERT_NOT(( has_yyy1< a3, int > ));
    MPL_ASSERT_NOT(( has_yyy2< a3, int, int > ));

    MPL_ASSERT_NOT(( has_xxx<a4> ));
    MPL_ASSERT_NOT(( has_xxx0< a4 > ));
    MPL_ASSERT_NOT(( has_xxx1< a4, int > ));
    MPL_ASSERT_NOT(( has_xxx2< a4, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< a4 > ));
    MPL_ASSERT_NOT(( has_yyy1< a4, int > ));
    MPL_ASSERT_NOT(( has_yyy2< a4, int, int > ));

#if !BOOST_WORKAROUND(__MWERKS__, BOOST_TESTED_AT(0x3202))
    MPL_ASSERT_NOT(( has_xxx<a5> ));
#endif
    MPL_ASSERT_NOT(( has_xxx< enum_ > ));
    MPL_ASSERT_NOT(( has_xxx0< enum_ > ));
    MPL_ASSERT_NOT(( has_xxx1< enum_, int > ));
    MPL_ASSERT_NOT(( has_xxx2< enum_, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< enum_ > ));
    MPL_ASSERT_NOT(( has_yyy1< enum_, int > ));
    MPL_ASSERT_NOT(( has_yyy2< enum_, int, int > ));
#endif

    MPL_ASSERT_NOT(( has_xxx<a1> ));
    MPL_ASSERT_NOT(( has_xxx0< a1 > ));
    MPL_ASSERT_NOT(( has_xxx1< a1, int > ));
    MPL_ASSERT_NOT(( has_xxx2< a1, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< a1 > ));
    MPL_ASSERT_NOT(( has_yyy1< a1, int > ));
    MPL_ASSERT_NOT(( has_yyy2< a1, int, int > ));

    MPL_ASSERT_NOT(( has_xxx< outer< inner<int> > > ));
    MPL_ASSERT_NOT(( has_xxx0< outer< inner<int> > > ));
    MPL_ASSERT_NOT(( has_xxx1< outer< inner<int> >, int > ));
    MPL_ASSERT_NOT(( has_xxx2< outer< inner<int> >, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< outer< inner<int> > > ));
    MPL_ASSERT_NOT(( has_yyy1< outer< inner<int> >, int > ));
    MPL_ASSERT_NOT(( has_yyy2< outer< inner<int> >, int, int > ));

    MPL_ASSERT_NOT(( has_xxx< incomplete > ));
    MPL_ASSERT_NOT(( has_xxx0< incomplete > ));
    MPL_ASSERT_NOT(( has_xxx1< incomplete, int > ));
    MPL_ASSERT_NOT(( has_xxx2< incomplete, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< incomplete > ));
    MPL_ASSERT_NOT(( has_yyy1< incomplete, int > ));
    MPL_ASSERT_NOT(( has_yyy2< incomplete, int, int > ));

    MPL_ASSERT_NOT(( has_xxx< abstract > ));
    MPL_ASSERT_NOT(( has_xxx0< abstract > ));
    MPL_ASSERT_NOT(( has_xxx1< abstract, int > ));
    MPL_ASSERT_NOT(( has_xxx2< abstract, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< abstract > ));
    MPL_ASSERT_NOT(( has_yyy1< abstract, int > ));
    MPL_ASSERT_NOT(( has_yyy2< abstract, int, int > ));

    MPL_ASSERT_NOT(( has_xxx< noncopyable > ));
    MPL_ASSERT_NOT(( has_xxx0< noncopyable > ));
    MPL_ASSERT_NOT(( has_xxx1< noncopyable, int > ));
    MPL_ASSERT_NOT(( has_xxx2< noncopyable, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< noncopyable > ));
    MPL_ASSERT_NOT(( has_yyy1< noncopyable, int > ));
    MPL_ASSERT_NOT(( has_yyy2< noncopyable, int, int > ));

#if !BOOST_WORKAROUND(__COMO_VERSION__, BOOST_TESTED_AT(4308))
    MPL_ASSERT_NOT(( has_xxx0< b1 > ));
    MPL_ASSERT_NOT(( has_xxx1< b1, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b1, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b1 > ));
    MPL_ASSERT_NOT(( has_yyy1< b1, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b1, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b2 > ));
    MPL_ASSERT_NOT(( has_xxx1< b2, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b2, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b2 > ));
    MPL_ASSERT_NOT(( has_yyy1< b2, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b2, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b3 > ));
    MPL_ASSERT_NOT(( has_xxx1< b3, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b3, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b3 > ));
    MPL_ASSERT_NOT(( has_yyy1< b3, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b3, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b4 > ));
    MPL_ASSERT_NOT(( has_xxx1< b4, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b4, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b4 > ));
    MPL_ASSERT_NOT(( has_yyy1< b4, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b4, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b5 > ));
    MPL_ASSERT_NOT(( has_xxx1< b5, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b5, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b5 > ));
    MPL_ASSERT_NOT(( has_yyy1< b5, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b5, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b6 > ));
    MPL_ASSERT_NOT(( has_xxx1< b6, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b6, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b6 > ));
    MPL_ASSERT_NOT(( has_yyy1< b6, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b6, int, int > ));

    MPL_ASSERT_NOT(( has_xxx0< b7 > ));
    MPL_ASSERT_NOT(( has_xxx1< b7, int > ));
    MPL_ASSERT_NOT(( has_xxx2< b7, int, int > ));
    MPL_ASSERT_NOT(( has_yyy0< b7 > ));
    MPL_ASSERT_NOT(( has_yyy1< b7, int > ));
    MPL_ASSERT_NOT(( has_yyy2< b7, int, int > ));
#endif

    // Same name, different args.
    //   Note: has_xxx0 is not test here because it's impossible to
    //   declare a template with no arguments (only no required
    //   arguments), so there is no zero argument substitute template
    //   to reject n-ary member templates.
#if (!BOOST_WORKAROUND(BOOST_MPL_CFG_GCC, <= 0x0303) \
     && !BOOST_WORKAROUND(__COMO_VERSION__, BOOST_TESTED_AT(4308)))
    MPL_ASSERT_NOT(( has_xxx1<c2, int> ));
    MPL_ASSERT_NOT(( has_xxx2<c0, int, int> ));
    MPL_ASSERT_NOT(( has_xxx2<c1, int, int> ));
#endif

    // Different name, same args.
    MPL_ASSERT_NOT(( has_xxx0<c3> ));
    MPL_ASSERT_NOT(( has_xxx1<c4, int> ));
    MPL_ASSERT_NOT(( has_xxx2<c5, int, int> ));

    // Different name, different args.
    MPL_ASSERT_NOT(( has_xxx0<c4> ));
    MPL_ASSERT_NOT(( has_xxx1<c5, int> ));
    MPL_ASSERT_NOT(( has_xxx2<c3, int, int> ));
    MPL_ASSERT_NOT(( has_xxx2<c4, int, int> ));

    MPL_ASSERT(( has_xxx<b1,true_> ));
    MPL_ASSERT(( has_xxx<b2,true_> ));
    MPL_ASSERT(( has_xxx<b3,true_> ));
    MPL_ASSERT(( has_xxx<b4,true_> ));
    MPL_ASSERT(( has_xxx<b5,true_> ));
    MPL_ASSERT(( has_xxx<b6,true_> ));
    MPL_ASSERT(( has_xxx<b7,true_> ));

#if !BOOST_WORKAROUND(__COMO_VERSION__, BOOST_TESTED_AT(4308)) && !BOOST_WORKAROUND(BOOST_MSVC, >= 1500)
    MPL_ASSERT(( has_xxx0<c0, true_> ));
    MPL_ASSERT(( has_yyy0<c3, true_> ));
#endif
    MPL_ASSERT(( has_xxx1<c1, int, true_> ));
    MPL_ASSERT(( has_xxx2<c2, int, int, true_> ));
    MPL_ASSERT(( has_yyy1<c4, int, true_> ));
    MPL_ASSERT(( has_yyy2<c5, int, int, true_> ));

#if !defined(HAS_XXX_ASSERT)
#   define HAS_XXX_ASSERT(x) MPL_ASSERT(x)
#endif

    HAS_XXX_ASSERT(( has_xxx<b1> ));
    HAS_XXX_ASSERT(( has_xxx<b2> ));
    HAS_XXX_ASSERT(( has_xxx<b3> ));
    HAS_XXX_ASSERT(( has_xxx<b4> ));
    HAS_XXX_ASSERT(( has_xxx<b5> ));
    HAS_XXX_ASSERT(( has_xxx<b6> ));
    HAS_XXX_ASSERT(( has_xxx<b7> ));

#if !defined(HAS_XXX_TEMPLATE_ASSERT)
#   define HAS_XXX_TEMPLATE_ASSERT(x) MPL_ASSERT(x)
#endif

#if !BOOST_WORKAROUND(__COMO_VERSION__, BOOST_TESTED_AT(4308)) && !BOOST_WORKAROUND(BOOST_MSVC, >= 1500)
    HAS_XXX_TEMPLATE_ASSERT(( has_xxx0<c0> ));
    HAS_XXX_TEMPLATE_ASSERT(( has_yyy0<c3> ));
#endif
    HAS_XXX_TEMPLATE_ASSERT(( has_xxx1<c1, int> ));
    HAS_XXX_TEMPLATE_ASSERT(( has_xxx2<c2, int, int> ));
    HAS_XXX_TEMPLATE_ASSERT(( has_yyy1<c4, int> ));
    HAS_XXX_TEMPLATE_ASSERT(( has_yyy2<c5, int, int> ));
}
