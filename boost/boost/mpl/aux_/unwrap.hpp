//-----------------------------------------------------------------------------
// boost mpl/aux_/unwrap.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
//  Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2001 David Abrahams
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
#define BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

#include "boost/ref.hpp"

namespace boost { namespace mpl { namespace aux {

template< typename F >
inline
F& unwrap(F& f, long)
{
    return f;
}

template< typename F >
inline
F&
unwrap(reference_wrapper<F>& f, int)
{
    return f;
}

template< typename F >
inline
F&
unwrap(reference_wrapper<F> const& f, int)
{
    return f;
}

}}} // namespace boost::mpl::aux

#endif // BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
