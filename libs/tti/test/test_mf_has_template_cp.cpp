
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_mf_has_template_cp.hpp"
#include <boost/detail/lightweight_test.hpp>

int main()
  {
  
  using namespace boost::mpl::placeholders;
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_TRAIT_GEN(HT_Str)<_>,
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(AnotherMemberTemplate)<_>,
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_TRAIT_GEN(WrongParametersForMP)<_>,
                boost::mpl::identity<AnotherType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(CTManyParameters)<_>,
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                  >
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist)<_>,
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                  >
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_TRAIT_GEN(MF_HT_Str),
                BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(AnotherMemberTemplate),
                boost::mpl::identity<AType>
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_TRAIT_GEN(MetaCWrongParametersForMP),
                boost::mpl::identity<AnotherType>
                >
              ::value
            ));
  
  BOOST_TEST((boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(CTManyParameters),
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                  >
                >
              ::value
            ));
  
  BOOST_TEST((!boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist),
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                  >
                >
              ::value
            ));
  
  return boost::report_errors();
  
  }
