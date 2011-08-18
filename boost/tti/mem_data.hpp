
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_MEMBER_DATA_HPP)
#define TTI_MEMBER_DATA_HPP

#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/remove_const.hpp>
#include "mf/mf_mem_data.hpp"
#include "gen/mem_data_gen.hpp"
#include "detail/dmem_data.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether a member data with a particular name and type exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.<br />
    
              The metafunction types and return:
    
                T   = the enclosing type in which to look for our 'name'.
                
                R   = the type of the member data.
                
                returns = 'value' is true if the 'name' exists, with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_TRAIT_HAS_MEMBER_DATA(trait,name) \
  TTI_DETAIL_TRAIT_HAS_MEMBER_DATA(trait,name) \
  template<class T,class R> \
  struct trait : \
    BOOST_PP_CAT(trait,_detail)<typename BOOST_TTI_NAMESPACE::detail::ptmd<T,R>::type,typename boost::remove_const<T>::type> \
    { \
    }; \
/**/

/// Expands to a metafunction which tests whether a member data with a particular name and type exists.
/**

    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::has_member_data_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                T   = the enclosing type in which to look for our 'name'.
                
                R   = the type of the member data.
                
                returns = 'value' is true if the 'name' exists, with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_HAS_MEMBER_DATA(name) \
  BOOST_TTI_TRAIT_HAS_MEMBER_DATA \
  ( \
  BOOST_TTI_HAS_MEMBER_DATA_GEN(name), \
  name \
  ) \
/**/

#endif // TTI_MEMBER_DATA_HPP
