
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_COMP_MEM_FUN_HPP)
#define BOOST_TTI_DETAIL_COMP_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/detail/dftclass.hpp>
#include <boost/tti/detail/dnullptr.hpp>
#include <boost/tti/gen/namespace_gen.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>

#define BOOST_TTI_DETAIL_TRAIT_HAS_COMP_MEMBER_FUNCTION(trait,name) \
  template<class T> \
  struct BOOST_PP_CAT(trait,_detail_hcmf) \
    { \
    template<class F> \
    struct cl_type : \
      boost::remove_const \
        < \
        typename BOOST_TTI_NAMESPACE::detail::class_type<F>::type \
        > \
      { \
      }; \
    \
    template<T> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type chkt(helper<&U::name> *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type chkt(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(chkt<typename cl_type<T>::type>(BOOST_TTI_DETAIL_NULLPTR))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#endif // BOOST_TTI_DETAIL_COMP_MEM_FUN_HPP
