
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_MEMBER_TYPE_HPP)
#define TEST_MF_MEMBER_TYPE_HPP

#include "test_structs.hpp"
#include <boost/tti/mem_type.hpp>

BOOST_TTI_MEMBER_TYPE(AnIntType)
BOOST_TTI_TRAIT_MEMBER_TYPE(NameStruct,AStructType)
BOOST_TTI_MEMBER_TYPE(AnIntTypeReference)
BOOST_TTI_MEMBER_TYPE(BType)
BOOST_TTI_TRAIT_MEMBER_TYPE(TheInteger,AnIntegerType)
BOOST_TTI_MEMBER_TYPE(CType)
BOOST_TTI_MEMBER_TYPE(AnotherIntegerType)
BOOST_TTI_TRAIT_MEMBER_TYPE(SomethingElse,someOtherType)

BOOST_TTI_MTFC_MEMBER_TYPE(AnIntType)
BOOST_TTI_MTFC_TRAIT_MEMBER_TYPE(MFNameStruct,AStructType)
BOOST_TTI_MTFC_MEMBER_TYPE(AnIntTypeReference)
BOOST_TTI_MTFC_MEMBER_TYPE(BType)
BOOST_TTI_MTFC_TRAIT_MEMBER_TYPE(MFTheInteger,AnIntegerType)
BOOST_TTI_MTFC_MEMBER_TYPE(CType)
BOOST_TTI_MTFC_MEMBER_TYPE(AnotherIntegerType)
BOOST_TTI_MTFC_TRAIT_MEMBER_TYPE(MetaClSomethingElse,someOtherType)

#endif // TEST_MF_MEMBER_TYPE_HPP
