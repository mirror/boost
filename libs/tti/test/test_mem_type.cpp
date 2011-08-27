
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mem_type.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/tti/mf/mf_member_type.hpp>

int main()
  {
  
  BOOST_TEST(boost::tti::mf_valid_member_type<BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<NameStruct<AType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<BOOST_TTI_MEMBER_TYPE_GEN(AnIntTypeReference)<AType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<TheInteger<AType::BType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<BOOST_TTI_MEMBER_TYPE_GEN(CType)<AType::BType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<BOOST_TTI_MEMBER_TYPE_GEN(AnotherIntegerType)<AType::BType::CType> >::value);
  BOOST_TEST(boost::tti::mf_valid_member_type<SomethingElse<AnotherType> >::value);
  
  return boost::report_errors();

  }
