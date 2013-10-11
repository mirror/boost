
//  Copyright 2001-2003 Aleksey Gurtovoy.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED
#define BOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/config.hpp>

#   define BOOST_TT_BROKEN_COMPILER_SPEC(T) /**/

BOOST_TT_BROKEN_COMPILER_SPEC(bool)
BOOST_TT_BROKEN_COMPILER_SPEC(char)
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
BOOST_TT_BROKEN_COMPILER_SPEC(wchar_t)
#endif
BOOST_TT_BROKEN_COMPILER_SPEC(signed char)
BOOST_TT_BROKEN_COMPILER_SPEC(unsigned char)
BOOST_TT_BROKEN_COMPILER_SPEC(signed short)
BOOST_TT_BROKEN_COMPILER_SPEC(unsigned short)
BOOST_TT_BROKEN_COMPILER_SPEC(signed int)
BOOST_TT_BROKEN_COMPILER_SPEC(unsigned int)
BOOST_TT_BROKEN_COMPILER_SPEC(signed long)
BOOST_TT_BROKEN_COMPILER_SPEC(unsigned long)
BOOST_TT_BROKEN_COMPILER_SPEC(float)
BOOST_TT_BROKEN_COMPILER_SPEC(double)
//BOOST_TT_BROKEN_COMPILER_SPEC(long double)

// for backward compatibility
#define BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(T) \
    BOOST_TT_BROKEN_COMPILER_SPEC(T) \
/**/

#endif // BOOST_TT_BROKEN_COMPILER_SPEC_HPP_INCLUDED
