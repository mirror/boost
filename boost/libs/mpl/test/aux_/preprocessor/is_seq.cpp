
// + file: libs/mpl/test/aux_/is_seq.cpp
// + last modified: 03/may/03

// Copyright (c) 2003
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

#include "boost/mpl/aux_/preprocessor/is_seq.hpp"

#include "boost/preprocessor/logical/not.hpp"
#include "boost/preprocessor/debug/assert.hpp"

#define AUX_ASSERT_IS_SEQ( seq ) \
    BOOST_PP_ASSERT( BOOST_MPL_PP_IS_SEQ(seq) ) \
/**/

#define AUX_ASSERT_IS_NOT_SEQ( seq ) \
    BOOST_PP_ASSERT( BOOST_PP_NOT( BOOST_MPL_PP_IS_SEQ(seq) ) ) \
/**/

#define SEQ (a)(b)(c)

int main()
{
    AUX_ASSERT_IS_NOT_SEQ( a )
    AUX_ASSERT_IS_SEQ( (a) )
    AUX_ASSERT_IS_SEQ( (a)(b) )
    AUX_ASSERT_IS_SEQ( (a)(b)(c) )
    AUX_ASSERT_IS_SEQ( SEQ )

    return 0;
}
