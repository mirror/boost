
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_COMP_STATIC_MEM_FUN_HPP)
#define TTI_COMP_STATIC_MEM_FUN_HPP

#include <boost/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include "gen/comp_static_mem_fun_gen.hpp"
#include "detail/dcomp_static_mem_fun.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction which tests whether a static member function with a particular name and composite type exists.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction types and return:
    
                T    = the enclosing type.
                
                Type = the static member function type,
                       in the form of a composite function type - 'return_type (parameter_types...)',
                       in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists within the enclosing type,
                          with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION(trait,name) \
      } \
    template<class T,class Type> \
    struct trait : \
      BOOST_TTI_NAMESPACE::detail::trait<T,Type> \
      { \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction class which tests whether a static member function with a particular name and composite type exists.
/**

    trait = the name of the metafunction class within the tti namespace.
    
    name  = the name of the inner member.

    returns = a metafunction class called "boost::tti::trait" where 'trait' is the macro parameter.<br />
    
              The metafunction class's 'apply' metafunction types and return:
    
                T    = the enclosing type.
                
                Type = the static member function type,
                       in the form of a composite function type - 'return_type (parameter_types...)',
                       in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists within the enclosing type,
                          with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_MTFC_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_MTFC_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION(trait,name) \
      } \
    struct trait \
      { \
      template<class T,class Type> \
      struct apply : \
        BOOST_TTI_NAMESPACE::detail::trait::apply<T,Type> \
        { \
        }; \
      }; \
    } \
  } \
/**/


/// Expands to a metafunction which tests whether a static member function with a particular name and composite type exists.
/**

    name  = the name of the inner member.

    returns = a metafunction called "boost::tti::has_comp_static_member_function_name" where 'name' is the macro parameter.<br />
    
              The metafunction types and return:
    
                T    = the enclosing type.
                
                Type = the static member function type,
                       in the form of a composite function type - 'return_type (parameter_types...)',
                       in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists within the enclosing type,
                          with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_HAS_COMP_STATIC_MEMBER_FUNCTION(name) \
  BOOST_TTI_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION \
  ( \
  BOOST_TTI_HAS_COMP_STATIC_MEMBER_FUNCTION_GEN_BASE(name), \
  name \
  ) \
/**/

/// Expands to a metafunction class which tests whether a static member function with a particular name and composite type exists.
/**

    name  = the name of the inner member.

    returns = a metafunction class called "boost::tti::mtfc_has_comp_static_member_function_name" where 'name' is the macro parameter.<br />
    
              The metafunction class's 'apply' metafunction types and return:
    
                T    = the enclosing type.
                
                Type = the static member function type,
                       in the form of a composite function type - 'return_type (parameter_types...)',
                       in which to look for our 'name'.
                       
                returns = 'value' is true if the 'name' exists within the enclosing type,
                          with the appropriate type,
                          otherwise 'value' is false.
                          
*/
#define BOOST_TTI_MTFC_HAS_COMP_STATIC_MEMBER_FUNCTION(name) \
  BOOST_TTI_MTFC_TRAIT_HAS_COMP_STATIC_MEMBER_FUNCTION \
  ( \
  BOOST_TTI_MTFC_HAS_COMP_STATIC_MEMBER_FUNCTION_GEN_BASE(name), \
  name \
  ) \
/**/

#endif // TTI_COMP_STATIC_MEM_FUN_HPP
