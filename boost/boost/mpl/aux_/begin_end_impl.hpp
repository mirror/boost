//-----------------------------------------------------------------------------
// boost mpl/aux_/begin_end_impl.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2000-02
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED

#include "boost/mpl/begin_end_fwd.hpp"
#include "boost/mpl/aux_/traits_lambda_spec.hpp"
#include "boost/mpl/aux_/config/eti.hpp"

namespace boost {
namespace mpl {

// default implementation; conrete sequences might override it by 
// specializing either the |begin_traits/end_traits| or the primary 
// |begin/end| templates

template< typename Tag >
struct begin_traits
{
    template< typename Sequence > struct algorithm
    {
        typedef typename Sequence::begin type;
    };
};

template< typename Tag >
struct end_traits
{
    template< typename Sequence > struct algorithm
    {
        typedef typename Sequence::end type;
    };
};

#if defined(BOOST_MPL_MSVC_ETI_BUG)
template<> struct begin_traits<int>
{
    template< typename Sequence > struct algorithm
    {
        typedef int type;
    };
};

template<> struct end_traits<int>
{
    template< typename Sequence > struct algorithm
    {
        typedef int type;
    };
};
#endif

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,begin_traits)
BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(1,end_traits)

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_BEGIN_END_IMPL_HPP_INCLUDED
