
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_fun.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_member_function
    <
    BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<_,_>,
    boost::mpl::identity<AnotherType>,
    boost::mpl::identity<short>
    > aVar;
  
  boost::tti::mf_has_member_function
    <
    BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(sFunction)<_,_,_>,
    boost::mpl::identity<AnotherType>,
    BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AnotherType>,
    boost::mpl::vector
      <
      boost::mpl::identity<int>,
      boost::mpl::identity<long>,
      boost::mpl::identity<double>
      >
    > aVar2;
                      
  boost::tti::mf_has_member_function
    <
    BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(someFunctionMember)<_,_,_>,
    boost::mpl::identity<AnotherType>,
    boost::mpl::identity<short>,
    boost::mpl::vector
      <
      boost::mpl::identity<double>,
      boost::mpl::identity<int>,
      boost::mpl::identity<long>
      >
    > aVar3;
    
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(VoidFunction)<_,_>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<void>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<_,_>,
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<int>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(FunctionReturningInt)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<double>,
                      boost::mpl::vector<boost::mpl::identity<int> >
                      >
                  ));
                  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_HAS_MEMBER_FUNCTION_GEN(aFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector<boost::mpl::identity<int> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(AnotherIntFunction)<_,_,_>,
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<int>,
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
                        boost::mpl::identity<int>,
                        boost::mpl::identity<long>,
                        boost::mpl::identity<double>
                        >
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN(VoidFunction),
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<void>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(MFFunctionReturningInt),
                      boost::mpl::identity<AType>,
                      boost::mpl::identity<int>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(MFFunctionReturningInt),
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<double>,
                      boost::mpl::vector<boost::mpl::identity<int> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN(aFunction),
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<AType>,
                      boost::mpl::vector<boost::mpl::identity<int> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_TRAIT_GEN(MFAnotherIntFunction),
                      boost::mpl::identity<AnotherType>,
                      boost::mpl::identity<int>,
                      boost::mpl::vector<boost::mpl::identity<AType> >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_member_function
                      <
                      BOOST_TTI_MTFC_HAS_MEMBER_FUNCTION_GEN(sFunction),
                      boost::mpl::identity<AnotherType>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>,
                      boost::mpl::vector
                        <
                        boost::mpl::identity<int>,
                        boost::mpl::identity<long>,
                        boost::mpl::identity<double> 
                        >
                      >
                  ));
  
  return 0;

  }
