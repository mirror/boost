//-----------------------------------------------------------------------------
// boost mpl/void.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2001-02
// Peter Dimov, Aleksey Gurtovoy
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_MPL_VOID_HPP_INCLUDED
#define BOOST_MPL_VOID_HPP_INCLUDED

namespace boost {
namespace mpl {

struct void_;

namespace aux {
template< typename > struct reject_if_void_ { enum { value = 1 }; };
template<> struct reject_if_void_<void_>; // never defined

template< typename > struct reject_if_not_void_; // never defined
template<> struct reject_if_not_void_<void_> { enum { value = 1 }; };
}

} // namespace mpl
} // namespace boost

#endif // BOOST_MPL_VOID_HPP_INCLUDED
