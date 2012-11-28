
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TTI_HAS_TYPE_HPP)
#define TTI_HAS_TYPE_HPP

#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/tti/gen/has_type_gen.hpp>
#include <boost/tti/gen/namespace_gen.hpp>
#include <boost/tti/detail/dtype.hpp>
#include <boost/tti/detail/ddeftype.hpp>

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/**

    BOOST_TTI_TRAIT_HAS_TYPE is a macro which expands to a metafunction.
    The metafunction tests whether an inner type with a particular name exists
    and, optionally, whether a second type is the same type as the inner type
    or whether a lambda expression invoked with the inner type is true or not.
    
    trait = the name of the metafunction within the tti namespace.
    
    name  = the name of the inner type.

    generates a metafunction called "trait" where 'trait' is the macro parameter.
    
              template<class TTI_T,class TTI_U,class TTI_B>
              struct trait
                {
                static const value = unspecified;
                typedef mpl::bool_<true-or-false> type;
                };

              The metafunction types and return:
    
                TTI_T = the enclosing type in which to look for our 'name'.
                
                TTI_U = (optional) An optional template parameter, defaulting to a marker type.. 
                                   If specified it is a type which is one of two possibilities.
                                   
                                   1) A type, which if specified, is checked to be the same as
                                      the inner type found.
                                      
                                   2) An MPL lambda expression which is invoked with the inner 
                                      type found and must return a constant boolean value.
                                      
                TTI_B = (optional) An optional template parameter of type boost::mpl::bool_,
                                   defaulting to boost::mpl::false_.
                                   
                                   If TTI_U is an MPL lambda expression, whose type is meant to 
                                   be checked to be the same as the inner type, rather than be 
                                   invoked by the inner type, this parameter shoud be set to
                                   boost::mpl::true_.
                
                returns = 'value' depends on whether or not the optional TTI_U is specified.
                
                          If TTI_U is not specified, then 'value' is true if the 'name' type 
                          exists within the enclosing type TTI_T, otherwise 'value' is false.
                          
                          If TTI_U is specified there are two possibiltities:
                          
                          1) TTI_U is an MPL lambda expression and TTI_B is not specified ( or 
                             specified as the default boost::mpl::false_ ), then 'value' is true 
                             if the 'name' type exists within the enclosing type TTI_T and the 
                             lambda expression as specified by TTI_U, invoked by passing the 
                             actual inner type of 'name', returns a 'value' of true, otherwise 
                             'value' is false.
                             
                          2) TTI_U is not an MPL lambda expression or TTI_B is boost::mpl::true_,
                             'value' is true if the 'name' type exists within the enclosing type 
                             TTI_T and the TTI_U type is the same as the actual inner type,
                             otherwise 'value' is false.
                             
                          In either case the action taken with TTI_U occurs only when the 'name'
                          type exists within the enclosing type TTI_T.
                             
  Example usage:
  
  BOOST_TTI_TRAIT_HAS_TYPE(LookFor,MyType) generates the metafunction LookFor in the current scope
  to look for an inner type called MyType.
  
  LookFor<EnclosingType>::value is true if MyType is an inner type of EnclosingType, otherwise false.
  
  LookFor<EnclosingType,AnotherType>::value is true if MyType is an inner type of EnclosingType
    and the inner type is the same type as AnotherType, otherwise false.
    
  LookFor<EnclosingType,ALambdaExpression>::value is true if MyType is an inner type of EnclosingType
    and invoking ALambdaExpression with the inner type returns a value of true, otherwise false.
  
  LookFor<EnclosingType,ALambdaExpression,boost::mpl::true_>::value is true if MyType is an inner type 
    of EnclosingType and the inner type is the same type as ALambdaExpression, otherwise false.
    
*/
#define BOOST_TTI_TRAIT_HAS_TYPE(trait,name) \
  BOOST_TTI_DETAIL_TRAIT_HAS_TYPE(trait,name) \
  template \
    < \
    class TTI_T, \
    class TTI_U = BOOST_TTI_NAMESPACE::detail::deftype, \
    class TTI_B = boost::mpl::false_ \
    > \
  struct trait : \
    BOOST_PP_CAT(trait,_detail_type) \
      < \
      TTI_T, \
      TTI_U, \
      TTI_B, \
      typename BOOST_PP_CAT(trait,_detail_type_mpl)<TTI_T>::type \
      > \
    { \
    }; \
/**/

/**

    BOOST_TTI_HAS_TYPE is a macro which expands to a metafunction.
    The metafunction tests whether an inner type with a particular name exists
    and, optionally, whether a second type is the same type as the inner type
    or whether a lambda expression invoked with the inner type is true or not.
    
    name  = the name of the inner type.

    generates a metafunction called "has_type_'name'" where 'name' is the macro parameter.
    
              template<class TTI_T,class TTI_U,class TTI_B>
              struct has_type_'name'
                {
                static const value = unspecified;
                typedef mpl::bool_<true-or-false> type;
                };

              The metafunction types and return:
    
                TTI_T = the enclosing type in which to look for our 'name'.
                
                TTI_U = (optional) An optional template parameter, defaulting to a marker type.. 
                                   If specified it is a type which is one of two possibilities.
                                   
                                   1) A type, which if specified, is checked to be the same as
                                      the inner type found.
                                      
                                   2) An MPL lambda expression which is invoked with the inner 
                                      type found and must return a constant boolean value.
                                      
                TTI_B = (optional) An optional template parameter of type boost::mpl::bool_,
                                   defaulting to boost::mpl::false_.
                                   
                                   If TTI_U is an MPL lambda expression, whose type is meant to 
                                   be checked to be the same as the inner type, rather than be 
                                   invoked by the inner type, this parameter shoud be set to
                                   boost::mpl::true_.
                
                returns = 'value' depends on whether or not the optional TTI_U is specified.
                
                          If TTI_U is not specified, then 'value' is true if the 'name' type 
                          exists within the enclosing type TTI_T, otherwise 'value' is false.
                          
                          If TTI_U is specified there are two possibiltities:
                          
                          1) TTI_U is an MPL lambda expression and TTI_B is not specified ( or 
                             specified as the default boost::mpl::false_ ), then 'value' is true 
                             if the 'name' type exists within the enclosing type TTI_T and the 
                             lambda expression as specified by TTI_U, invoked by passing the 
                             actual inner type of 'name', returns a 'value' of true, otherwise 
                             'value' is false.
                             
                          2) TTI_U is not an MPL lambda expression or TTI_B is boost::mpl::true_,
                             'value' is true if the 'name' type exists within the enclosing type 
                             TTI_T and the TTI_U type is the same as the actual inner type,
                             otherwise 'value' is false.
                             
                          In either case the action taken with TTI_U occurs only when the 'name'
                          type exists within the enclosing type TTI_T.
                             
  Example usage:
  
  BOOST_TTI_HAS_TYPE(MyType) generates the metafunction has_type_MyType in the current scope
  to look for an inner type called MyType.
  
  has_type_MyType<EnclosingType>::value is true if MyType is an inner type of EnclosingType, otherwise false.
  
  has_type_MyType<EnclosingType,AnotherType>::value is true if MyType is an inner type of EnclosingType
    and the inner type is the same type as AnotherType, otherwise false.
    
  has_type_MyType<EnclosingType,ALambdaExpression>::value is true if MyType is an inner type of EnclosingType
    and invoking ALambdaExpression with the inner type returns a value of true, otherwise false.
  
  has_type_MyType<EnclosingType,ALambdaExpression,boost::mpl::true_>::value is true if MyType is an inner type 
    of EnclosingType and the inner type is the same type as ALambdaExpression, otherwise false.
    
*/
#define BOOST_TTI_HAS_TYPE(name) \
  BOOST_TTI_TRAIT_HAS_TYPE \
  ( \
  BOOST_TTI_HAS_TYPE_GEN(name), \
  name \
  ) \
/**/

#endif // TTI_HAS_TYPE_HPP
