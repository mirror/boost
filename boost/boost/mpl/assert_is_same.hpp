//-----------------------------------------------------------------------------
// boost mpl/assert_is_same.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_ASSERT_IS_SAME_HPP_INCLUDED
#define BOOST_MPL_ASSERT_IS_SAME_HPP_INCLUDED

#include "boost/static_assert.hpp"
#include "boost/type_traits/same_traits.hpp"

namespace boost {
namespace mpl {

// the following macros are shortcuts for some often-used but verbose forms 
// of static asserts

// tokenization takes place before macro expansion (see 2.1 [lex.phases] 
// para 3-4), so, strictly speaking, spaces between '<', 'type1', and 
// 'type2', '>' tokens below are not required; they are needed in practice,
// though, because there is at least one compiler (MSVC 6.5) that does not
// conform to the standard here

#define BOOST_MPL_ASSERT_IS_SAME(type1, type2) \
    BOOST_STATIC_ASSERT((::boost::is_same< type1, type2 >::value)) \
/**/

#define BOOST_MPL_ASSERT_NOT_SAME(type1, type2) \
    BOOST_STATIC_ASSERT(!(::boost::is_same< type1, type2 >::value)) \
/**/

} // namespace mpl
} // namespace boost 

#endif // BOOST_MPL_ASSERT_IS_SAME_HPP_INCLUDED
