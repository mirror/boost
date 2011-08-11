
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_MEMBER_TYPE_HPP)
#define TTI_MEMBER_TYPE_HPP
  
#include <boost/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include "mf/mf_mem_type.hpp"
#include "gen/mem_type_gen.hpp"
#include "detail/dmem_type.hpp"
#include "detail/dnotype.hpp"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/// Expands to a metafunction whose typedef 'type' is either the named type or an unspecified type.
/**

    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner type.

    returns = a metafunction called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction types and return:
              
                T = the enclosing type.<br />
                
                returns = 'type' is the inner type of 'name' if the inner type exists
                          within the enclosing type, else 'type' is an unspecified type.<br />
                          
    The purpose of this macro is to encapsulate the 'name' type as the typedef 'type'
    of a metafunction, but only if it exists within the enclosing type. This allows for
    a lazy evaluation of inner type existence which can be used by other metafunctions
    in this library.
    
*/
#define BOOST_TTI_TRAIT_MEMBER_TYPE(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_TYPE_MEMBER_TYPE(trait,name) \
      TTI_DETAIL_TRAIT_MEMBER_TYPE(trait,name) \
      } \
    template<class T> \
    struct trait : \
      boost::mpl::eval_if \
        < \
        BOOST_TTI_NAMESPACE::detail::trait<T>, \
        BOOST_TTI_NAMESPACE::detail::member_type::trait<T>, \
        boost::mpl::identity<BOOST_TTI_NAMESPACE::detail::notype> \
        > \
      { \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction class whose typedef 'type' is either the named type or an unspecified type.
/**

    trait = the name of the metafunction class within the tti namespace.
    
    name  = the name of the inner type.

    returns = a metafunction class called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
              
                T = the enclosing type.
                
                returns = 'type' is the inner type of 'name' if the inner type exists
                          within the enclosing type, else 'type' is an unspecified type.<br />
                          
    The purpose of this macro is to encapsulate the 'name' type as the typedef 'type'
    of a metafunction class, but only if it exists within the enclosing type. This allows for
    a lazy evaluation of inner type existence which can be used by other metafunctions
    in this library.
    
*/
#define BOOST_TTI_MTFC_TRAIT_MEMBER_TYPE(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_TYPE_MEMBER_TYPE(trait,name) \
      TTI_DETAIL_TRAIT_MEMBER_TYPE(trait,name) \
      } \
    struct trait \
      { \
      template<class T> \
      struct apply : \
        boost::mpl::eval_if \
          < \
          BOOST_TTI_NAMESPACE::detail::trait<T>, \
          BOOST_TTI_NAMESPACE::detail::member_type::trait<T>, \
          boost::mpl::identity<BOOST_TTI_NAMESPACE::detail::notype> \
          > \
        { \
        }; \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction whose typedef 'type' is either the named type or an unspecified type.
/**

    name  = the name of the inner type.

    returns = a metafunction called "boost::tti::member_type_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
              
                T = the enclosing type.
                
                returns = 'type' is the inner type of 'name' if the inner type exists
                          within the enclosing type, else 'type' is an unspecified type.
                          
    The purpose of this macro is to encapsulate the 'name' type as the typedef 'type'
    of a metafunction, but only if it exists within the enclosing type. This allows for
    a lazy evaluation of inner type existence which can be used by other metafunctions
    in this library.
    
*/
#define BOOST_TTI_MEMBER_TYPE(name) \
  BOOST_TTI_TRAIT_MEMBER_TYPE \
  ( \
  BOOST_TTI_MEMBER_TYPE_GEN_BASE(name), \
  name \
  ) \
/**/
  
/// Expands to a metafunction class whose typedef 'type' is either the named type or an unspecified type.
/**

    name  = the name of the inner type.

    returns = a metafunction class called "boost::tti::mtfc_member_type_name" where 'name' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
              
                T = the enclosing type.
                
                returns = 'type' is the inner type of 'name' if the inner type exists
                          within the enclosing type, else 'type' is an unspecified type.
                          
    The purpose of this macro is to encapsulate the 'name' type as the typedef 'type'
    of a metafunction class, but only if it exists within the enclosing type. This allows for
    a lazy evaluation of inner type existence which can be used by other metafunctions
    in this library.
    
*/
#define BOOST_TTI_MTFC_MEMBER_TYPE(name) \
  BOOST_TTI_MTFC_TRAIT_MEMBER_TYPE \
  ( \
  BOOST_TTI_MTFC_MEMBER_TYPE_GEN_BASE(name), \
  name \
  ) \
/**/

#endif // TTI_MEMBER_TYPE_HPP
