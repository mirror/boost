
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_has_static_mem_fun.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  // You can always instantiate without compiler errors
  
  BOOST_TTI_TRAIT_GEN(TheTIntFunction)<AType,void,boost::mpl::vector<long,double> > aVar;
  BOOST_TTI_TRAIT_GEN(Pickedname)<AnotherType,AType,boost::mpl::vector<long,long> > aVar3;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(HaveTheSIntFunction)<AType,int,boost::mpl::vector<long,double> >));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(TheTIntFunction)<AnotherType,AType,boost::mpl::vector<long,double> >));
  BOOST_MPL_ASSERT((BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_GEN(TSFunction)<AnotherType,AType::AStructType,boost::mpl::vector<AType::AnIntType,double> >));
  
  return 0;

  }
