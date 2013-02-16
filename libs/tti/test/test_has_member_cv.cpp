
//  (C) Copyright Edward Diener 2013
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_mem_fun.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  BOOST_TEST((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AConstFunction)<double (AType::*)(long,char) const>::value));
  BOOST_TEST((StillTest<AType (AnotherType::*)(int) const>::value));
  BOOST_TEST((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AnotherConstFunction)<int (AnotherType::*)(AType *, short) const>::value));
  BOOST_TEST((AskIfConst<void (AType::*)(float,double) const>::value));
  
  return boost::report_errors();

  }
