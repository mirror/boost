
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_type_ct.hpp"
#include <boost/detail/lightweight_test.hpp>
#include <boost/tti/mf/mf_has_type.hpp>
#include <boost/tti/mf/mf_member_type.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_TEST((boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(AnIntType)<_,_>,
                boost::mpl::identity<AType>,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                NameStruct<_,_>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)<_,_>,
                boost::mpl::identity<AType>,
                int &
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(BType)<_,_>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                TheInteger<_,_>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(CType)<_,_>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>,
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)<_,_>,
                boost::tti::mf_member_type
                  <
                  boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(CType)>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                SomethingElse<_,_>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((!boost::tti::mf_has_type
                <
                BOOST_TTI_HAS_TYPE_GEN(NoOtherType)<_,_>,
                boost::mpl::identity<AnotherType>,
                double
                >
              ::value
            ));

  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(AnIntType)>,
                boost::mpl::identity<AType>,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<NameStruct>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(AnIntTypeReference)>,
                boost::mpl::identity<AType>,
                int &
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(BType)>,
                boost::mpl::identity<AType>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<TheInteger>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(CType)>,
                BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>,
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(AnotherIntegerType)>,
                boost::tti::mf_member_type
                  <
                  boost::mpl::quote1<BOOST_TTI_MEMBER_TYPE_GEN(CType)>,
                  BOOST_TTI_MEMBER_TYPE_GEN(BType)<AType>
                  >,
                int
                >
              ::value
            ));
            
  BOOST_TEST((boost::tti::mf_has_type
                <
                boost::mpl::quote2<SomethingElse>,
                boost::mpl::identity<AnotherType>,
                BOOST_TTI_MEMBER_TYPE_GEN(AnIntType)<AType>
                >
              ::value
            ));
            
  BOOST_TEST((!boost::tti::mf_has_type
                <
                boost::mpl::quote2<BOOST_TTI_HAS_TYPE_GEN(NoOtherType)>,
                boost::mpl::identity<AnotherType>,
                double
                >
              ::value
            ));
  
  return boost::report_errors();

  }
