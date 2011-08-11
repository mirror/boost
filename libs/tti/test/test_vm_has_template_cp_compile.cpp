
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#include "test_vm_has_template_cp.hpp"
#include <boost/mpl/assert.hpp>

int main()
  {
  
#if !defined(BOOST_NO_VARIADIC_MACROS)

  // You can always instantiate without compiler errors
  
  BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(TemplateNotExist)<AnotherType> aVar1;
  
  // Compile time asserts
  
  BOOST_MPL_ASSERT((BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(ATPMemberTemplate)<AType>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(HaveCL)<AType>));
  BOOST_MPL_ASSERT((BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(AMemberTemplate)<AType>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(HaveAnotherMT)<AType>));
  BOOST_MPL_ASSERT((BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(SomeMemberTemplate)<AnotherType>));
  BOOST_MPL_ASSERT((BOOST_TTI_TRAIT_GEN(ATemplateWithParms)<AnotherType>));
  BOOST_MPL_ASSERT((BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS_GEN(SimpleTMP)<AnotherType>));
  
#endif //!defined(BOOST_NO_VARIADIC_MACROS)

  return 0;

  }
