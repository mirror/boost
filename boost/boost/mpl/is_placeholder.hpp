//-----------------------------------------------------------------------------
// boost mpl/is_placeholder.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
#define BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED

#include "boost/mpl/arg_fwd.hpp"
#include "boost/mpl/bool.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/config/ctps.hpp"
#include "boost/mpl/aux_/config/nttp.hpp"

namespace boost { namespace mpl {

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< typename T >
struct is_placeholder
    : bool_<false>
{
};

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct is_placeholder< arg<N> >
    : bool_<true>
{
};

#else

namespace aux {

aux::no_tag is_placeholder_helper(...);

template< BOOST_MPL_AUX_NTTP_DECL(int, N) >
aux::yes_tag is_placeholder_helper(arg<N>*);

} // namespace aux

template< typename T >
struct is_placeholder
{
    BOOST_STATIC_CONSTANT(bool, value = 
        sizeof(aux::is_placeholder_helper(static_cast<T*>(0))) == sizeof(aux::yes_tag)
    );
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

}} // namespace boost::mpl

#endif // BOOST_MPL_IS_PLACEHOLDER_HPP_INCLUDED
