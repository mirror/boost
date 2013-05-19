
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_STATIC_MEM_FUN_HPP)
#define BOOST_TTI_DETAIL_STATIC_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/function_types/is_function.hpp>
#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/detail/dnullptr.hpp>
#include <boost/tti/detail/dtfunction.hpp>
#include <boost/tti/gen/namespace_gen.hpp>
#include <boost/type_traits/detail/yes_no_type.hpp>
#include <boost/type_traits/is_same.hpp>

#define BOOST_TTI_DETAIL_TRAIT_IMPL_HAS_STATIC_MEMBER_FUNCTION(trait,name) \
  template<class T,class Type> \
  struct BOOST_PP_CAT(trait,_detail_ihsmf) \
    { \
    template<Type *> \
    struct helper; \
    \
    template<class U> \
    static ::boost::type_traits::yes_type chkt(helper<&U::name> *); \
    \
    template<class U> \
    static ::boost::type_traits::no_type chkt(...); \
    \
    BOOST_STATIC_CONSTANT(bool,value=sizeof(chkt<T>(BOOST_TTI_DETAIL_NULLPTR))==sizeof(::boost::type_traits::yes_type)); \
    \
    typedef boost::mpl::bool_<value> type; \
    }; \
/**/

#define BOOST_TTI_DETAIL_TRAIT_HAS_STATIC_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_IMPL_HAS_STATIC_MEMBER_FUNCTION(trait,name) \
  template<class TTI_T,class TTI_R,class TTI_FS,class TTI_TAG> \
  struct BOOST_PP_CAT(trait,_detail_hsmf) : \
    BOOST_PP_CAT(trait,_detail_ihsmf) \
      < \
      TTI_T, \
      typename \
      boost::mpl::eval_if \
        < \
        boost::mpl::and_ \
          < \
          boost::function_types::is_function<TTI_R>, \
          boost::is_same<TTI_FS,boost::mpl::vector<> >, \
          boost::is_same<TTI_TAG,boost::function_types::null_tag> \
          >, \
        boost::mpl::identity<TTI_R>, \
        BOOST_TTI_NAMESPACE::detail::tfunction_seq<TTI_R,TTI_FS,TTI_TAG> \
        >::type \
      > \
    { \
    }; \
/**/

#endif // BOOST_TTI_DETAIL_STATIC_MEM_FUN_HPP
