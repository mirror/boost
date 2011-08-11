
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_static_member.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST((BOOST_TTI_TRAIT_GEN(HaveTheSIntFunction)<AType,int (long,double)>::value));
  BOOST_TEST((!BOOST_TTI_TRAIT_GEN(TheTIntFunction)<AType,AType (long,double)>::value));
  BOOST_TEST((BOOST_TTI_TRAIT_GEN(TheTIntFunction)<AnotherType,AType (long,double)>::value));
  BOOST_TEST((BOOST_TTI_HAS_COMP_STATIC_MEMBER_FUNCTION_GEN(TSFunction)<AnotherType,AType::AStructType (AType::AnIntType,double)>::value));
  BOOST_TEST((!BOOST_TTI_TRAIT_GEN(Pickedname)<AnotherType,void ()>::value));
  
  return boost::report_errors();

  }
