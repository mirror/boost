
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Source$
// $Date$
// $Revision$

#include <boost/mpl/size_t.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#include "integral_wrapper_test.hpp"

MPL_TEST_CASE()
{
#   define WRAPPER(T, i) mpl::size_t<i>
    BOOST_PP_REPEAT_FROM_TO(1, 11, INTEGRAL_WRAPPER_TEST, std::size_t)
}
