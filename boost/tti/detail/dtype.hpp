
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_DETAIL_TYPE_HPP)
#define TTI_DETAIL_TYPE_HPP

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_same.hpp>
#include "dnotype.hpp"

#define TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
namespace ttimpl \
  { \
  BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(trait, name, false) \
  } \
template<class T,class U,class B> \
struct trait \
  { \
  typedef typename \
    boost::mpl::eval_if \
      < \
      boost::is_same<typename T::name,U>, \
      boost::mpl::true_, \
      boost::mpl::false_ \
      >::type \
  type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
\
template<class T,class U> \
struct trait<T,U,boost::mpl::false_::type> \
  { \
  typedef boost::mpl::false_::type type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
\
template<class T> \
struct trait<T,notype,boost::mpl::true_::type> \
  { \
  typedef boost::mpl::true_::type type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
/**/

#endif // TTI_DETAIL_TYPE_HPP
