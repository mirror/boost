
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_mem_data.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/tti/mf/mf_has_member_data.hpp>
#include <boost/tti/mf/mf_member_type.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                BOOST_TTI_HAS_MEMBER_DATA_GEN(AnInt)<_,_>,
                boost::mpl::identity<AType>,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                BOOST_TTI_HAS_MEMBER_DATA_GEN(AnInt)<_,_>,
                boost::mpl::identity<AnotherType>,
                long 
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                BOOST_TTI_HAS_MEMBER_DATA_GEN(aMember)<_,_>,
                boost::mpl::identity<AnotherType>,
                bool 
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                CMember<_,_>,
                boost::mpl::identity<AnotherType>,
                bool 
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                BOOST_TTI_HAS_MEMBER_DATA_GEN(IntBT)<_,_>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                NestedData<_,_>,
                boost::mpl::identity<AType>,
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                AOther<_,_>,
                boost::mpl::identity<AnotherType>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                BOOST_TTI_HAS_MEMBER_DATA_GEN(ONestStr)<_,_>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<BOOST_TTI_HAS_MEMBER_DATA_GEN(AnInt)>,
                boost::mpl::identity<AType>,
                int 
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<BOOST_TTI_HAS_MEMBER_DATA_GEN(AnInt)>,
                boost::mpl::identity<AnotherType>,
                long 
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<BOOST_TTI_HAS_MEMBER_DATA_GEN(aMember)>,
                boost::mpl::identity<AnotherType>,
                bool 
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<CMember>,
                boost::mpl::identity<AnotherType>,
                bool 
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<BOOST_TTI_HAS_MEMBER_DATA_GEN(IntBT)>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<NestedData>,
                boost::mpl::identity<AType>,
                boost::tti::mf_member_type
                  <
                  boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(CType)>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<AOther>,
                boost::mpl::identity<AnotherType>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_member_data
                <
                boost::mpl::quote2<BOOST_TTI_HAS_MEMBER_DATA_GEN(ONestStr)>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  return boost::report_errors();

  }
