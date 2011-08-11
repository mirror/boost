
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_vm_mf_has_template_cp.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
#if !defined(BOOST_NO_VARIADIC_MACROS)

  using namespace boost::mpl::placeholders;
  
  // You can always instantiate without compiler errors
  
  boost::tti::mf_has_template_check_params
                <
                BOOST_TTI_VM_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist),
                boost::tti::mf_member_type
                  <
                  BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                  BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                  >
                > aVar;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_TRAIT_GEN(HT_Str)<_>,
                      BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(AnotherMemberTemplate)<_>,
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(CTManyParameters)<_>,
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MTFC_MEMBER_TYPE_GEN(CType),
                        BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                        >
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_TRAIT_GEN(MF_HT_Str),
                      BOOST_TTI_MEMBER_TYPE_GEN(AStructType)<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_VM_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(AnotherMemberTemplate),
                      boost::mpl::identity<AType>
                      >
                  ));
  
  BOOST_MPL_ASSERT((boost::tti::mf_has_template_check_params
                      <
                      BOOST_TTI_VM_MTFC_HAS_TEMPLATE_CHECK_PARAMS_GEN(CTManyParameters),
                      boost::tti::mf_member_type
                        <
                        BOOST_TTI_MEMBER_TYPE_GEN(CType)<_>,
                        BOOST_TTI_TRAIT_GEN(MT_BType)<AType>
                        >
                      >
                  ));
  
#endif //!defined(BOOST_NO_VARIADIC_MACROS)

  return 0;
  
  }
