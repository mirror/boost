
// (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. This software 
// is provided "as is" without express or implied warranty, and with no claim 
// as to its suitability for any purpose.
//
// See http://www.boost.org for most recent version including documentation.

#ifndef BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED
#define BOOST_TT_IS_BASE_AND_DERIVED_HPP_INCLUDED

#include "boost/type_traits/is_class.hpp"
#include "boost/type_traits/is_convertible.hpp"
#include "boost/type_traits/detail/ice_and.hpp"
#include "boost/config.hpp"

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail {

template <typename Base, typename Derived>
struct is_base_and_derived_impl
{
   BOOST_STATIC_CONSTANT(bool, value =
      (::boost::type_traits::ice_and<
         ::boost::is_convertible<Derived*,Base*>::value,
         ::boost::is_class<Derived>::value,
         ::boost::is_class<Base>::value
      >::value)
   );
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
