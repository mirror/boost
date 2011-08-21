
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_TYPE_HPP)
#define TTI_TYPE_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/mf/mf_type.hpp>
#include <boost/tti/gen/type_gen.hpp>
#include <boost/tti/detail/dtype.hpp>
#include <boost/tti/detail/dnotype.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether an inner type with a particular name exists and optionally is a particular type.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner type.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction types and return:
    
                TTI_T = the enclosing type in which to look for our 'name'.
                
                TTI_U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_TRAIT_HAS_TYPE(trait,name) \
  TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
  template<class TTI_T,class TTI_U = BOOST_TTI_NAMESPACE::detail::notype> \
  struct trait : \
    BOOST_PP_CAT(trait,_detail) \
      < \
      TTI_T, \
      TTI_U, \
      typename BOOST_PP_CAT(trait,_detail_mpl)<TTI_T>::type \
      > \
    { \
    }; \
/**/

/// Expands to a metafunction which tests whether an inner type with a particular name exists and optionally is a particular type.
/**

    name  = the name of the inner type.

    returns = a metafunction called "boost::tti::has_type_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                TTI_T = the enclosing type in which to look for our 'name'.
                
                TTI_U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_HAS_TYPE(name) \
  BOOST_TTI_TRAIT_HAS_TYPE \
  ( \
  BOOST_TTI_HAS_TYPE_GEN(name), \
  name \
  ) \
/**/

#endif // TTI_TYPE_HPP
