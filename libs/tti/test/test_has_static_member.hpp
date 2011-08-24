
//  (C) Copyright Edward Diener 2011
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(TEST_HAS_STATIC_MEMBER_HPP)
#define TEST_HAS_STATIC_MEMBER_HPP

#include "test_structs.hpp"
#include <boost/tti/has_static_member_function_with_sig.hpp>

BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_WITH_SIG(HaveTheSIntFunction,SIntFunction)
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_WITH_SIG(TheTIntFunction,TIntFunction)
BOOST_TTI_HAS_STATIC_MEMBER_FUNCTION_WITH_SIG(TSFunction)
BOOST_TTI_TRAIT_HAS_STATIC_MEMBER_FUNCTION_WITH_SIG(Pickedname,SomeStaticFunction)

#endif // TEST_HAS_STATIC_MEMBER_HPP
