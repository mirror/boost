//-----------------------------------------------------------------------------
// boost mpl/protect.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MPL_PROTECT_HPP_INCLUDED
#define BOOST_MPL_PROTECT_HPP_INCLUDED

#include "boost/mpl/aux_/arity.hpp"
#include "boost/mpl/aux_/config/dtp.hpp"
#include "boost/mpl/aux_/void_spec.hpp"

namespace boost {
namespace mpl {

template<
      typename BOOST_MPL_AUX_VOID_SPEC_PARAM(T)
    >
struct protect : T
{
    typedef struct protect type;
};

#if defined(BOOST_BROKEN_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES)
namespace aux { 
template< BOOST_MPL_AUX_NTTP_DECL(int, N), typename T >
struct arity< protect<T>, N > 
    : arity<T,N>
{ 
};
} // namespace aux
#endif

BOOST_MPL_AUX_VOID_SPEC_MAIN(1, protect)
#if !defined(BOOST_MPL_NO_FULL_LAMBDA_SUPPORT)
BOOST_MPL_AUX_VOID_SPEC_TEMPLATE_ARITY(1, 1, protect)
#endif

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_PROTECT_HPP_INCLUDED
