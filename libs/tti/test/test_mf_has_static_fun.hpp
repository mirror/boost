
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_HAS_STATIC_FUNCTION_HPP)
#define TEST_MF_HAS_STATIC_FUNCTION_HPP

#include "test_structs.hpp"
#include <boost/tti/static_mem_fun.hpp>
#include <boost/tti/mem_type.hpp>

BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION(HaveTheSIntFunction,SIntFunction)
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION(TheTIntFunction,TIntFunction)
BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION(TSFunction)
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION(Pickedname,SomeStaticFunction)

BOOST_TTI_MTFC_TRAIT_HAS_STATIC_MEMBER_FUNCTION(MFHaveTheSIntFunction,SIntFunction)
BOOST_TTI_MTFC_TRAIT_HAS_STATIC_MEMBER_FUNCTION(MFCTheTIntFunction,TIntFunction)
BOOST_TTI_MTFC_HAS_STATIC_MEMBER_FUNCTION(TSFunction)
BOOST_TTI_MTFC_TRAIT_HAS_STATIC_MEMBER_FUNCTION(MTFCPickedname,SomeStaticFunction)

BOOST_TTI_MEMBER_TYPE(AStructType)
BOOST_TTI_TRAIT_MEMBER_TYPE(NameIntType,AnIntType)

#endif // TEST_MF_HAS_STATIC_FUNCTION_HPP
