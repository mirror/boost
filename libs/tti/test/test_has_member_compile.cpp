
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_member.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // You can always instantiate without compiler errors
  
  BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(someFunctionMember)<double (AnotherType::*)(short,short,long,int)> aVar3;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(VoidFunction)<void (AType::*)()>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<int (AType::*)()>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<double (AnotherType::*)(int)>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(aFunction)<AType (AnotherType::*)(int)>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(AnotherIntFunction)<int (AnotherType::*)(AType)>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_COMP_MEMBER_FUNCTION_GEN(sFunction)<AType::AnIntType (AnotherType::*)(int,long,double)>));
  
  return 0;

  }
