//-----------------------------------------------------------------------------
// boost mpl/aux_/template_arity.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED
#define BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED

#include "boost/mpl/aux_/template_arity_fwd.hpp"
#include "boost/mpl/aux_/has_rebind.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {
namespace aux {

// gcc ICEs on |has_rebind|
#if !defined(__GNUC__)

template< bool >
struct template_arity_impl
{
    template< typename F > struct result_
    {
        BOOST_STATIC_CONSTANT(int, value = -1);
    };
};

template<>
struct template_arity_impl<true>
{
    template< typename F > struct result_
    {
        typedef typename F::rebind f_;
        BOOST_STATIC_CONSTANT(int, value = f_::arity);
    };
};

template< typename F >
struct template_arity
    : template_arity_impl< ::boost::mpl::aux::has_rebind<F>::value >
        ::template result_<F>
{
};

#else

template< typename F >
struct template_arity
{
    BOOST_STATIC_CONSTANT(int, value = -1);
};

#endif // __GNUC__

#if defined(BOOST_MSVC) && BOOST_MSVC == 1300
// workaround for MSVC 7.0 "early template instantiation bug"
template<>
struct template_arity<int>
{
    BOOST_STATIC_CONSTANT(int, value = -1);
};
#endif

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_TEMPLATE_ARITY_HPP_INCLUDED
