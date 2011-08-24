
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_MF_HAS_MEMBER_FUNCTION_HPP)
#define TEST_MF_HAS_MEMBER_FUNCTION_HPP

#include "test_structs.hpp"
#include <boost/tti/has_member_function.hpp>
#include <boost/tti/member_type.hpp>

BOOST_TTI_HAS_MEMBER_FUNCTION(VoidFunction)
BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION(FunctionReturningInt,IntFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(aFunction)
BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION(AnotherIntFunction,anotherFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(sFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(someFunctionMember)

BOOST_TTI_MEMBER_TYPE(AnIntType)

#endif // TEST_MF_HAS_MEMBER_FUNCTION_HPP
