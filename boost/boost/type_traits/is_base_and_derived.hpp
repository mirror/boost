
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


