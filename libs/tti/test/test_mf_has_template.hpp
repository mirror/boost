
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_HAS_TEMPLATE_HPP)
#define TEST_MF_HAS_TEMPLATE_HPP

#include "test_structs.hpp"
#include <boost/tti/template.hpp>
#include <boost/tti/mem_type.hpp>

BOOST_TTI_TRAIT_HAS_TEMPLATE(HaveMStr,MStrMemberTemplate)
BOOST_TTI_HAS_TEMPLATE(TemplateNotExist)
BOOST_TTI_HAS_TEMPLATE(ATPMemberTemplate)
BOOST_TTI_TRAIT_HAS_TEMPLATE(HaveCL,CLMemberTemplate)
BOOST_TTI_HAS_TEMPLATE(SimpleTMP)
BOOST_TTI_TRAIT_HAS_TEMPLATE(AMT,AnotherMemberTemplate)
BOOST_TTI_HAS_TEMPLATE(SomeMemberTemplate)

BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE(MetaHaveMStr,MStrMemberTemplate)
BOOST_TTI_MTFC_HAS_TEMPLATE(TemplateNotExist)
BOOST_TTI_MTFC_HAS_TEMPLATE(ATPMemberTemplate)
BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE(MFClassHaveCL,CLMemberTemplate)
BOOST_TTI_MTFC_HAS_TEMPLATE(SimpleTMP)
BOOST_TTI_MTFC_TRAIT_HAS_TEMPLATE(MFClassAMT,AnotherMemberTemplate)
BOOST_TTI_MTFC_HAS_TEMPLATE(SomeMemberTemplate)

BOOST_TTI_MEMBER_TYPE(AStructType)
BOOST_TTI_TRAIT_MEMBER_TYPE(MT_BType,BType)

#endif // TEST_MF_HAS_TEMPLATE_HPP
