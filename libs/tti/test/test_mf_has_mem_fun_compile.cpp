
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_fun.hpp"
#include <boost/mpl/assert.hpp>
#include <boost/tti/mf/mf_has_member_function.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_member_function
    <
    FunctionReturningInt<_,_>,
    boost::mpl::identity<AnotherType>,
    short
    > aVar;
  
  boost::tti::mf_has_member_function
    <
    BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)<_,_,_>,
    boost::mpl::identity<AnotherType>,
    BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AnotherType>,
    boost::mpl::vector
      <
      int,
      long,
      double
      >
    > aVar2;
                      
  boost::tti::mf_has_member_function
    <
    BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(someFunctionMember)<_,_,_>,
    boost::mpl::identity<AnotherType>,
    short,
    boost::mpl::vector
      <
      double,
      int,
      long
      >
    > aVar3;
    
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)<_,_>,
                      boost::mpl::identity<AType>,
                      void
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      FunctionReturningInt<_,_>,
                      boost::mpl::identity<AType>,
                      int
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      FunctionReturningInt<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      double,
                      boost::mpl::vector<int>
                      >
                  ));
                  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector<int>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      AnotherIntFunction<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      int,
                      boost::mpl::vector<boost::mpl::identity<AType> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>,
                      boost::mpl::vector
                        <
                        int,
                        long,
                        double
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)>,
                      boost::mpl::identity<AType>,
                      void
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<FunctionReturningInt>,
                      boost::mpl::identity<AType>,
                      int
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<FunctionReturningInt>,
                      boost::mpl::identity<AnotherType>,
                      double,
                      boost::mpl::vector<int>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector<int>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<AnotherIntFunction>,
                      boost::mpl::identity<AnotherType>,
                      int,
                      boost::mpl::vector<boost::mpl::identity<AType> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      boost::mpl::quote4<BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)>,
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>,
                      boost::mpl::vector
                        <
                        int,
                        long,
                        double 
                        >
                      >
                  ));
  
  return 0;

  }
