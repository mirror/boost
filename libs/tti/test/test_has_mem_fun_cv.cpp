
//  (C) Copyright Edward Diener 2012
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_mem_fun.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  // Use const enclosing type
  
  BOOST_TEST((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AConstFunction)<const AType,double,boost::mpl::vector<long,char> >::value));
  BOOST_TEST((StillTest<const AnotherType,AType,boost::mpl::vector<int> >::value));
  
  // Use const_qualified
  
  BOOST_TEST((BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(AnotherConstFunction)<AnotherType,int,boost::mpl::vector<AType *, short>,boost::function_types::const_qualified>::value));
  BOOST_TEST((AskIfConst<AType,void,boost::mpl::vector<float,double>,boost::function_types::const_qualified>::value));
  
  return boost::report_errors();

  }
