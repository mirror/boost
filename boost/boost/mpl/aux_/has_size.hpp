//-----------------------------------------------------------------------------
// boost mpl/aux_/has_size.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_AUX_HAS_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_HAS_SIZE_HPP_INCLUDED

#include "boost/mpl/aux_/type_wrapper.hpp"
#include "boost/mpl/aux_/yes_no.hpp"
#include "boost/mpl/aux_/config/msvc_typename.hpp"
#include "boost/mpl/aux_/config/overload_resolution.hpp"
#include "boost/config.hpp"

namespace boost {
namespace mpl {
namespace aux {

#if !defined(BOOST_MPL_BROKEN_OVERLOAD_RESOLUTION)

// the implementation below is based on a USENET newsgroup posting by  
// Rani Sharoni (comp.lang.c++.moderated, 2002-03-17 07:45:09 PST)

template< typename T >
yes_tag has_size_helper(type_wrapper<T>*, BOOST_MSVC_TYPENAME T::size*);

template< typename T >
no_tag has_size_helper(type_wrapper<T>*, ...);

template< typename T >
struct has_size
{
     BOOST_STATIC_CONSTANT(bool, value = 
        sizeof(has_size_helper((type_wrapper<T>*)0, 0)) == sizeof(yes_tag)
        );
};

#else

template< typename T >
struct has_size
{
     BOOST_STATIC_CONSTANT(bool, value = false);
};

#endif

} // namespace aux
} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_AUX_HAS_SIZE_HPP_INCLUDED
