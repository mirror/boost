//-----------------------------------------------------------------------------
// boost mpl/aux_/has_rebind.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED

#include "boost/mpl/aux_/has_xxx.hpp"
#include "boost/mpl/if.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/type_traits/is_class.hpp"

namespace boost { namespace mpl { namespace aux {

BOOST_MPL_HAS_XXX_TRAIT_NAMED_DEF(has_rebind_impl, rebind, false)

template< typename T >
struct has_rebind
    : if_c< 
          ::boost::is_class<T>::value
        , has_rebind_impl<T>
        , bool_<false>
        >::type
{
};

}}}

#endif // BOOST_MPL_AUX_HAS_REBIND_HPP_INCLUDED
