
// + file: libs/mpl/test/aux_/template_arity.cpp
// + last modified: 10/jul/03

// Copyright (c) 2000-03
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/template_arity.hpp"
#include "boost/static_assert.hpp"

#   if defined(BOOST_EXTENDED_TEMPLATE_PARAMETERS_MATCHING)

using namespace boost::mpl;

struct my {};
template< typename T1 > struct my1 {};
template< typename T1, typename T2 = void > struct my2 {};

int main()
{
    BOOST_STATIC_ASSERT((aux::template_arity<my>::value == -1));
    BOOST_STATIC_ASSERT((aux::template_arity< my1<int> >::value == 1));
    BOOST_STATIC_ASSERT((aux::template_arity< my2<int,long> >::value == 2));
    BOOST_STATIC_ASSERT((aux::template_arity< my2<int> >::value == 2));
    
    return 0;
}

#   endif
