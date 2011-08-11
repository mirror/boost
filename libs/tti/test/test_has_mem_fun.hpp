
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_HAS_MEMBER_FUNCTION_HPP)
#define TEST_HAS_MEMBER_FUNCTION_HPP

#include "test_structs.hpp"
#include <boost/tti/mem_fun.hpp>

BOOST_TTI_HAS_MEMBER_FUNCTION(VoidFunction)
BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION(FunctionReturningInt,IntFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(aFunction)
BOOST_TTI_TRAIT_HAS_MEMBER_FUNCTION(AnotherIntFunction,anotherFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(sFunction)
BOOST_TTI_HAS_MEMBER_FUNCTION(someFunctionMember)
BOOST_TTI_HAS_MEMBER_FUNCTION(PublicIntFunction)

#endif // TEST_HAS_MEMBER_FUNCTION_HPP
