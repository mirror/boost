
//  (C) John Maddock 2005.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED
#define BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED

#include "boost/type_traits/type_with_alignment.hpp"
#include <boost/type_traits/is_pod.hpp>

// should be the last #include
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace boost {

namespace detail{

template <class T, std::size_t N>
struct storage
{
   union
   {
      char m_buf[N];
      T m_align;
   };
};

}

#ifndef BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
template <class T, std::size_t K>
struct is_pod<boost::detail::storage<T,K> >
   BOOST_TT_AUX_BOOL_C_BASE(true)
{ 
    BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL(true)
}; 
#endif

template <std::size_t Len, std::size_t Align>
struct aligned_storage
{
   typedef typename type_with_alignment<Align>::type  aligned_type;
   typedef detail::storage<aligned_type,Len>          type;
};

} // namespace boost

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // BOOST_TT_ALIGNED_STORAGE_HPP_INCLUDED
