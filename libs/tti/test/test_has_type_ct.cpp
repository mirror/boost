
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_type_ct.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnIntType)<AType,int>::value));
  BOOST_TEST((NameStruct<AType,AType::AStructType>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)<AType,int &>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(BType)<AType,AType::BType>::value));
  BOOST_TEST((TheInteger<AType::BType,int>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(CType)<AType::BType,AType::BType::CType>::value));
  BOOST_TEST((BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)<AType::BType::CType,int>::value));
  BOOST_TEST((SomethingElse<AnotherType,AType::AnIntType>::value));
  BOOST_TEST((!BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<AnotherType,double>::value));
  
  return boost::report_errors();

  }
