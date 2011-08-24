
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_VM_HAS_TEMPLATE_CHECK_PARAMS_HPP)
#define TEST_VM_HAS_TEMPLATE_CHECK_PARAMS_HPP

#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include "test_structs.hpp"
#include <boost/tti/vm_has_template_check_params.hpp>

BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS(ATPMemberTemplate,class)
BOOST_TTI_VM_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveCL,CLMemberTemplate,class,class)
BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS(AMemberTemplate,int)
BOOST_TTI_VM_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HaveAnotherMT,AnotherMemberTemplate,int,int)
BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS(SomeMemberTemplate,class,class,class,class,class,class)
BOOST_TTI_VM_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(ATemplateWithParms,ManyParameters,class,class,int,class,template <class> class InnerTemplate,class,long)
BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS(SimpleTMP,class,class,class,class)
BOOST_TTI_VM_HAS_TEMPLATE_CHECK_PARAMS(TemplateNotExist,int,class,template <class> class ATemplate)
BOOST_TTI_VM_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParametersForMP,ManyParameters,class,class,int,class,template <class,class> class InnerTemplate,class,long)
BOOST_TTI_VM_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParameters2ForMP,ManyParameters,class,long,int,class,template <class> class InnerTemplate,class,long)

#endif // BOOST_PP_VARIADICS

#endif // TEST_VM_HAS_TEMPLATE_CHECK_PARAMS_HPP
