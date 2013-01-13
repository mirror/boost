
//  (C) Copyright Edward Diener 2011,2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_mem_fun.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // You can always instantiate without compiler errors
  
  BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(someFunctionMember)<double (AnotherType::*)(short,short,long,int)> aVar3;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)<void (AType::*)()>));
  BOOST_MPL_ASSERT((FunctionReturningInt<int (AType::*)()>));
  BOOST_MPL_ASSERT((FunctionReturningInt<double (AnotherType::*)(int)>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)<AType (AnotherType::*)(int)>));
  BOOST_MPL_ASSERT((AnotherIntFunction<int (AnotherType::*)(AType)>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)<AType::AnIntType (AnotherType::*)(int,long,double)>));
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AConstFunction)<double (AType::*)(long,char) const>));
  BOOST_MPL_ASSERT((StillTest<const AType * (AnotherType::*)(int) const>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AnotherConstFunction)<int (AnotherType::*)(const AType *, short) const>));
  BOOST_MPL_ASSERT((AskIfConst<void (AType::*)(float,double) const>));
  
  return 0;

  }
