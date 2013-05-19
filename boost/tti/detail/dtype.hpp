
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_DETAIL_TYPE_HPP)
#define BOOST_TTI_DETAIL_TYPE_HPP

#include <boost/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/detail/ddeftype.hpp>
#include <boost/tti/detail/dlambda.hpp>
#include <boost/tti/gen/namespace_gen.hpp>

#define BOOST_TTI_DETAIL_TRAIT_INVOKE_HAS_TYPE(trait,name) \
template<class TTI_T,class TTI_MFC> \
struct BOOST_PP_CAT(trait,_detail_type_invoke) : \
  boost::mpl::apply<TTI_MFC,typename TTI_T::name> \
  { \
  }; \
/**/

#define BOOST_TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(BOOST_PP_CAT(trait,_detail_type_mpl), name, false) \
BOOST_TTI_DETAIL_TRAIT_INVOKE_HAS_TYPE(trait,name) \
template<class TTI_T,class TTI_U,class TTI_B> \
struct BOOST_PP_CAT(trait,_detail_type) \
  { \
  BOOST_MPL_ASSERT((BOOST_TTI_NAMESPACE::detail::is_lambda_expression<TTI_U>)); \
  typedef typename BOOST_PP_CAT(trait,_detail_type_invoke)<TTI_T,TTI_U>::type type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
\
template<class TTI_T,class TTI_U> \
struct BOOST_PP_CAT(trait,_detail_type)<TTI_T,TTI_U,boost::mpl::false_::type> \
  { \
  typedef boost::mpl::false_::type type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
\
template<class TTI_T> \
struct BOOST_PP_CAT(trait,_detail_type)<TTI_T,BOOST_TTI_NAMESPACE::detail::deftype,boost::mpl::true_::type> \
  { \
  typedef boost::mpl::true_::type type; \
  BOOST_STATIC_CONSTANT(bool,value=type::value); \
  }; \
/**/

#endif // BOOST_TTI_DETAIL_TYPE_HPP
