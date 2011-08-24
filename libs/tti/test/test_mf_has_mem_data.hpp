
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_HAS_MEMBER_DATA_HPP)
#define TEST_MF_HAS_MEMBER_DATA_HPP

#include "test_structs.hpp"
#include <boost/tti/has_member_data.hpp>
#include <boost/tti/member_type.hpp>

BOOST_TTI_HAS_MEMBER_DATA(AnInt)
BOOST_TTI_HAS_MEMBER_DATA(aMember)
BOOST_TTI_TRAIT_HAS_MEMBER_DATA(CMember,cMem)
BOOST_TTI_HAS_MEMBER_DATA(someDataMember)
BOOST_TTI_HAS_MEMBER_DATA(IntBT)
BOOST_TTI_TRAIT_HAS_MEMBER_DATA(NestedData,NestedCT)
BOOST_TTI_TRAIT_HAS_MEMBER_DATA(AOther,OtherAT)
BOOST_TTI_HAS_MEMBER_DATA(ONestStr)

BOOST_TTI_MEMBER_TYPE(BType)
BOOST_TTI_MEMBER_TYPE(CType)
BOOST_TTI_MEMBER_TYPE(AStructType)

#endif // TEST_MF_HAS_MEMBER_DATA_HPP
