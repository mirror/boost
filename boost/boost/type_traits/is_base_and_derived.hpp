
// (C) Copyright Rani Sharoni 2002.
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. This software 
// is provided "as is" without express or implied warranty, and with no claim 
// as to its suitability for any purpose.
//
// See http://www.boost.org for most recent version including documentation.

#ifndef BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED
#define BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED

#include "boost/type_traits/is_class.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_convertible.hpp"
#include "boost/type_traits/detail/ice_and.hpp"
#include "boost/type_traits/remove_cv.hpp"
#include "boost/config.hpp"

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail {

#if !defined(__BORLANDC__)

/*************************************************************************

This version detects ambiguous base classes and private base classes
correctly, and was devised by Rani Sharoni.

The following explanation is by Terje Slettebo:

Let's take the multiple base class below as an example, and the
following will also show why there's not a problem with ambiguous base
class:

struct B {};
struct B1 : B {};
struct B2 : B {};
struct D : B1, private B2 {};

typedef char Test[is_base_and_derived<B, D>::result]; // improvement 1 -
multiple base


We have several possible conversion sequences:

For "static no check(B const volatile *, int)" we have the conversion
sequences:
   C -> C const -> B*
and
   C -> D* -> B1*|B2* -> B*

For "static yes check(D const volatile *, T)" we have the conversion
sequence:
   C -> D*

Since, for the purpose of selecting the appropriate user-defined conversion
for a given function, it only considers up to the user-defined conversion,
for the first function this means choosing between C -> C const and C -> C,
and it chooses the latter. Therefore, we have:

C -> D* -> B1*|B2* -> B*
C -> D*

Here, the principle of the "shortest subsequence" applies, and it chooses
C -> D*. This shows that it doesn't even need to consider the multiple paths
to B, as that possibility is eliminated before it could possibly cause
ambiguity. Nifty. :)

As Daveed notes in the posting Rani gives a link to in the clc++m posting,
if D is not derived from B, it has to choose between C -> C const -> B* for
the first function, and C -> D* for the second function, which are just as
good, _had it not been for the fact that "static no check(B const volatile
&, int)" is not templated (as Rani points out in the posting)_, which makes
C -> C const -> B* the best choice, resulting in "no".

Also, if C::operator B* hadn't been const, the two conversion sequences for
"static no check(B const volatile *, int)" would have been ambiguous.

See also http://groups.google.com/groups?selm=df893da6.0301280859.522081f7%40posting.google.com
and links therein.

*************************************************************************/

template <typename B, typename D>
struct bd_helper
{
    template <typename T>
    static type_traits::yes_type check(D const volatile *, T);
    static type_traits::no_type  check(B const volatile *, int);
};

template<typename B, typename D>
struct is_base_and_derived_impl2
{
    struct Host
    {
        operator B const volatile *() const;
        operator D const volatile *();
    };

    BOOST_STATIC_CONSTANT(bool, value =
        sizeof(bd_helper<B,D>::check(Host(), 0)) == sizeof(type_traits::yes_type));
};

#else

//
// broken version:
//
template<typename B, typename D>
struct is_base_and_derived_impl2
{
    BOOST_STATIC_CONSTANT(bool, value =
        (::boost::is_convertible<D*,B*>::value));
};

#define BOOST_BROKEN_IS_BASE_AND_DERIVED

#endif

template <typename B, typename D>
struct is_base_and_derived_impl3
{
    BOOST_STATIC_CONSTANT(bool, value = false);
};

template <bool ic1, bool ic2, bool iss>
struct is_base_and_derived_select
{
   template <class T, class U>
   struct rebind
   {
      typedef is_base_and_derived_impl3<T,U> type;
   };
};

template <>
struct is_base_and_derived_select<true,true,false>
{
   template <class T, class U>
   struct rebind
   {
      typedef is_base_and_derived_impl2<T,U> type;
   };
};

template <typename B, typename D>
struct is_base_and_derived_impl
{
    typedef typename remove_cv<B>::type ncvB;
    typedef typename remove_cv<D>::type ncvD;

    typedef is_base_and_derived_select<
       ::boost::is_class<B>::value,
       ::boost::is_class<D>::value,
       ::boost::is_same<B,D>::value> selector;
    typedef typename selector::template rebind<ncvB,ncvD> binder;
    typedef typename binder::type bound_type;

    BOOST_STATIC_CONSTANT(bool, value = bound_type::value);
};

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF2(
      is_base_and_derived
    , Base
    , Derived
    , (::boost::detail::is_base_and_derived_impl<Base,Derived>::value)
    )

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base&,Derived,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base,Derived&,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_base_and_derived,Base&,Derived&,false)
#endif

} // namespace boost

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED


