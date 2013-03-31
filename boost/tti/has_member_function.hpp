
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(BOOST_TTI_HAS_MEMBER_FUNCTION_HPP)
#define BOOST_TTI_HAS_MEMBER_FUNCTION_HPP

#include <boost/function_types/property_tags.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/detail/ddeftype.hpp>
#include <boost/tti/detail/dmem_fun.hpp>
#include <boost/tti/gen/has_member_function_gen.hpp>
#include <boost/tti/gen/namespace_gen.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether a member function with a particular name and signature exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner member.

    generates a metafunction called "trait" where 'trait' is the macro parameter.<br />
    
              template<class TTI_T,class TTI_R,class TTI_FS,class TTI_TAG>
              struct trait
                {
                static const value = unspecified;
                typedef mpl::bool_<true-or-false> type;
                };

              The metafunction types and return:
    
                TTI_T   = the enclosing type in which to look for our 'name'
                                            OR
                          a pointer to member function as a single type.
                
                TTI_R   = (optional) the return type of the member function
                          if the first parameter is the enclosing type.
                
                TTI_FS  = (optional) the parameters of the member function as a boost::mpl forward sequence
                          if the first parameter is the enclosing type and the member function parameters
                          are not empty.
                
                TTI_TAG = (optional) a boost::function_types tag to apply to the member function
                          if the first parameter is the enclosing type and a tag is needed.
                
                returns = 'value' is true if the 'name' exists, 
                          with the appropriate member function type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_MEMBER_FUNCTION(trait,name) \
  template<class TTI_T,class TTI_R = BOOST_TTI_NAMESPACE::detail::deftype,class TTI_FS = boost::mpl::vector<>,class TTI_TAG = boost::function_types::null_tag> \
  struct trait : \
    BOOST_PP_CAT(trait,_detail_hmf)<TTI_T,TTI_R,TTI_FS,TTI_TAG> \
    { \
    }; \
/**/

/// Expands to a metafunction which tests whether a member function with a particular name and signature exists.
/**

    name  = the name of the inner member.

    generates a metafunction called "has_member_function_name" where 'name' is the macro parameter.
    
              template<class TTI_T,class TTI_R,class TTI_FS,class TTI_TAG>
              struct has_member_function_name
                {
                static const value = unspecified;
                typedef mpl::bool_<true-or-false> type;
                };

              The metafunction types and return:
    
                TTI_T   = the enclosing type in which to look for our 'name'
                                            OR
                          a pointer to member function as a single type.
                
                TTI_R   = (optional) the return type of the member function
                          if the first parameter is the enclosing type.
                
                TTI_FS  = (optional) the parameters of the member function as a boost::mpl forward sequence
                          if the first parameter is the enclosing type and the member function parameters
                          are not empty.
                
                TTI_TAG = (optional) a boost::function_types tag to apply to the member function
                          if the first parameter is the enclosing type and a tag is needed.
                
                returns = 'value' is true if the 'name' exists, 
                          with the appropriate member function type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_HAS_MEMBER_FUNCTION(name) \
  BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION \
  ( \
  BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(name), \
  name \
  ) \
/**/

#endif // BOOST_TTI_HAS_MEMBER_FUNCTION_HPP
