//-----------------------------------------------------------------------------
// boost mpl/test/is_placeholder.cpp source file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include "boost/mpl/is_placeholder.hpp"
#include "boost/mpl/placeholders.hpp"

#include "boost/preprocessor/repeat.hpp"
#include "boost/preprocessor/inc.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/static_assert.hpp"

using namespace boost::mpl;

struct UDT;
    
#define AUX_IS_PLACEHOLDER_TEST(unused1, n, unused2) \
    { BOOST_STATIC_ASSERT(is_placeholder< \
          BOOST_PP_CAT(_,BOOST_PP_INC(n)) \
        >::value); } \
/**/

int main()
{
    BOOST_STATIC_ASSERT(!is_placeholder<int>::value);
    BOOST_STATIC_ASSERT(!is_placeholder<UDT>::value);
    BOOST_STATIC_ASSERT(is_placeholder<_>::value);
    
    BOOST_PP_REPEAT(
          BOOST_MPL_METAFUNCTION_MAX_ARITY
        , AUX_IS_PLACEHOLDER_TEST
        , unused
        )
        
    return 0;
}
