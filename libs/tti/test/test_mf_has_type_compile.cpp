
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_type.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_type
    <
    BOOST_TTI_MTFC_HAS_TYPE_GEN(AnIntType),
    boost::mpl::identity<AnotherType>
    > aVar;
  
  boost::tti::mf_has_type
    <
    BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<_>,
    boost::mpl::identity<AnotherType>
    > aVar2;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(AnIntType)<_>,
                      boost::mpl::identity<AType>
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(NameStruct)<_>,
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)<_>,
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(BType)<_>,
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(TheInteger)<_>,
                      BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(CType)<_>,
                      BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)<_>,
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(SomethingElse)<_>,
                      boost::mpl::identity<AnotherType>
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_MTFC_HAS_TYPE_GEN(AnIntType),
                      boost::mpl::identity<AType>
                      >
                  ));
            
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(MetaFNameStruct),
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_MTFC_HAS_TYPE_GEN(AnIntTypeReference),
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_MTFC_HAS_TYPE_GEN(BType),
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(MClassTheInteger),
                      BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_MTFC_HAS_TYPE_GEN(CType),
                      BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_MTFC_HAS_TYPE_GEN(AnotherIntegerType),
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                        BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_type
                      <
                      BOOST_TTI_TRAIT_GEN(MTFCSomethingElse),
                      boost::mpl::identity<AnotherType>
                      >
                  ));
            
  return 0;

  }
