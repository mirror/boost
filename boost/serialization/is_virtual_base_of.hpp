//  (C) Copyright Daniel Frey and Robert Ramey 2009.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.
 
#ifndef BOOST_TT_IS_VIRTUAL_BASE_OF_HPP_INCLUDED
#define BOOST_TT_IS_VIRTUAL_BASE_OF_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/detail/ice_not.hpp>
#include <boost/type_traits/detail/ice_and.hpp>

// should be the last #include
#include <boost/type_traits/detail/bool_trait_def.hpp>

namespace boost {
namespace detail {


#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable : 4584 )
#endif

template<typename Base, typename Derived>
struct is_virtual_base_of_impl
{
    struct X : Derived, virtual Base {};
    BOOST_STATIC_CONSTANT(bool, value = sizeof(X)==sizeof(Derived));
};

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

} // namespace detail

BOOST_TT_AUX_BOOL_TRAIT_DEF2(
      is_virtual_base_of
    , Base
    , Derived
    , (::boost::type_traits::ice_and<      
         (::boost::detail::is_virtual_base_of_impl<Base,Derived>::value),
         (::boost::type_traits::ice_not<
            (::boost::is_same<Base,Derived>::value)
         >::value)
    >::value)
)

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base&,Derived,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base,Derived&,false)
BOOST_TT_AUX_BOOL_TRAIT_PARTIAL_SPEC2_2(typename Base,typename Derived,is_virtual_base_of,Base&,Derived&,false)
#endif

} // namespace boost

#include <boost/type_traits/detail/bool_trait_undef.hpp>

#endif
