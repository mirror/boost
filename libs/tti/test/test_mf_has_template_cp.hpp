
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_HAS_TEMPLATE_CHECK_PARAMS_HPP)
#define TEST_MF_HAS_TEMPLATE_CHECK_PARAMS_HPP

#include "test_structs.hpp"
#include <boost/tti/template_params.hpp>
#include <boost/tti/mem_type.hpp>

BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(HT_Str,MStrMemberTemplate,(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(AnotherMemberTemplate,(int)(int))
BOOST_TTI_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(WrongParametersForMP,ManyParameters,(class)(class)(int)(class)(template <class> class InnerTemplate)(class)(short))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(CTManyParameters,(class)(class)(int)(short)(class)(template <class)(int> class InnerTemplate)(class))
BOOST_TTI_HAS_TEMPLATE_CHECK_PARAMS(TemplateNotExist,(int)(class))

BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(MF_HT_Str,MStrMemberTemplate,(class))
BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS(AnotherMemberTemplate,(int)(int))
BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE_CHECK_PARAMS(MetaCWrongParametersForMP,ManyParameters,(class)(class)(int)(class)(template <class> class InnerTemplate)(class)(short))
BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS(CTManyParameters,(class)(class)(int)(short)(class)(template <class)(int> class InnerTemplate)(class))
BOOST_TTI_MTFC_HAS_TEMPLATE_CHECK_PARAMS(TemplateNotExist,(int)(class))

BOOST_TTI_MEMBER_TYPE(AStructType)
BOOST_TTI_TRAIT_MEMBER_TYPE(MT_BType,BType)
BOOST_TTI_MEMBER_TYPE(CType)

BOOST_TTI_MTFC_MEMBER_TYPE(CType)

#endif // TEST_MF_HAS_TEMPLATE_CHECK_PARAMS_HPP
