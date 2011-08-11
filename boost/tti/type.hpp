
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_TYPE_HPP)
#define TTI_TYPE_HPP

#include <boost/config.hpp>
#include "mf/mf_type.hpp"
#include "gen/type_gen.hpp"
#include "detail/dtype.hpp"
#include "detail/dnotype.hpp"

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
    
                T = the enclosing type in which to look for our 'name'.
                
                U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_TRAIT_HAS_TYPE(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
      } \
    template<class T,class U = BOOST_TTI_NAMESPACE::detail::notype> \
    struct trait : \
      BOOST_TTI_NAMESPACE::detail::trait \
        < \
        T, \
        U, \
        typename BOOST_TTI_NAMESPACE::detail::ttimpl::trait<T>::type \
        > \
      { \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction class which tests whether an inner type with a particular name exists and optionally is a particular type.
/**

    trait = the name of the metafunction class within the tti namespace.
    
    name  = the name of the inner type.

    returns = a metfunction class called "boost::tti::trait" where 'trait' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_MTFC_TRAIT_HAS_TYPE(trait,name) \
namespace boost \
  { \
  namespace tti \
    { \
    namespace detail \
      { \
      TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
      } \
    struct trait \
      { \
      template<class T,class U = BOOST_TTI_NAMESPACE::detail::notype> \
      struct apply : \
        BOOST_TTI_NAMESPACE::detail::trait \
          < \
          T, \
          U, \
          typename BOOST_TTI_NAMESPACE::detail::ttimpl::trait<T>::type \
          > \
        { \
        }; \
      }; \
    } \
  } \
/**/

/// Expands to a metafunction which tests whether an inner type with a particular name exists and optionally is a particular type.
/**

    name  = the name of the inner type.

    returns = a metafunction called "boost::tti::has_type_name" where 'name' is the macro parameter.
    
              The metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_HAS_TYPE(name) \
  BOOST_TTI_TRAIT_HAS_TYPE \
  ( \
  BOOST_TTI_HAS_TYPE_GEN_BASE(name), \
  name \
  ) \
/**/

/// Expands to a metafunction class which tests whether an inner type with a particular name exists and optionally is a particular type.
/**

    name  = the name of the inner type.

    returns = a metafunction class called "boost::tti::mtfc_has_type_name" where 'name' is the macro parameter.
    
              The metafunction class's 'apply' metafunction types and return:
    
                T = the enclosing type in which to look for our 'name'.
                
                U = the type of the inner type named 'name' as an optional parameter.
                
                returns = 'value' is true if the 'name' type exists within the enclosing type
                          and, if type U is specified, the 'name' type is the same as the type U,
                          otherwise 'value' is false.
    
*/
#define BOOST_TTI_MTFC_HAS_TYPE(name) \
  BOOST_TTI_MTFC_TRAIT_HAS_TYPE \
  ( \
  BOOST_TTI_MTFC_HAS_TYPE_GEN_BASE(name), \
  name \
  ) \
/**/

#endif // TTI_TYPE_HPP
