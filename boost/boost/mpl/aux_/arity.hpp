//-----------------------------------------------------------------------------
// boost mpl/aux_/arity.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_AUX_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_ARITY_HPP_INCLUDED

#include "boost/mpl/aux_/config/dtp.hpp"
#include "boost/mpl/aux_/config/nttp.hpp"

#if defined(BOOST_BROKEN_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)

#   include "boost/config.hpp"

namespace boost {
namespace mpl {
namespace aux {

// agurt, 15/mar/02: it's possible to implement the template so that it will 
// "just work" and do not require any specialization, but not on the compilers
// that require the arity workaround in the first place
template< typename F, BOOST_MPL_AUX_NTTP_DECL(int, N) >
struct arity
{
    BOOST_STATIC_CONSTANT(int, value = N);
};

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_BROKEN_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES

#endif // BOOST_MPL_AUX_ARITY_HPP_INCLUDED
