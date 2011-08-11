
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_DETAIL_MEM_TYPE_HPP)
#define TTI_DETAIL_MEM_TYPE_HPP

#include <boost/config.hpp>
#include <boost/mpl/has_xxx.hpp>

#define TTI_DETAIL_TRAIT_HAS_TYPE_MEMBER_TYPE(trait,name) \
namespace ttimpl \
  { \
  BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, false) \
  } \
template<class T> \
struct trait \
  { \
  typedef typename ttimpl::trait<T>::type type; \
  \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
/**/

#define TTI_DETAIL_TRAIT_MEMBER_TYPE(trait,name) \
namespace member_type \
  { \
  template<class T> \
  struct trait \
    { \
    typedef typename T::name type; \
    }; \
  } \
/**/

#endif // TTI_DETAIL_MEM_TYPE_HPP
