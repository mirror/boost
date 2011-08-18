
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_type_ct.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // You can always instantiate without compiler errors
  
  TheInteger<AType::BType,short> aVar;
  BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<AnotherType,double> aVar2;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TYPE_GEN(AnIntType)<AType,int>));
  BOOST_MPL_ASSERT((NameStruct<AType,AType::AStructType>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)<AType,int &>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TYPE_GEN(BType)<AType,AType::BType>));
  BOOST_MPL_ASSERT((TheInteger<AType::BType,int>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TYPE_GEN(CType)<AType::BType,AType::BType::CType>));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)<AType::BType::CType,int>));
  BOOST_MPL_ASSERT((SomethingElse<AnotherType,AType::AnIntType>));
  
  return 0;

  }
