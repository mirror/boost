//-----------------------------------------------------------------------------
// boost mpl/aux_/config/ntp.hpp header file
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

#ifndef BOOST_MPL_AUX_CONFIG_NTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_NTP_HPP_INCLUDED

#include "boost/config.hpp"

// MSVC 6.5 ICE-s on the code as simple as this:
/*
    namespace std {
    template< typename Char > struct string;
    }

    void foo(std::string<char>);

    namespace boost {
    namespace mpl {

    template< int > struct arg;

    }}
*/
// the only way to get around the bug is to replace the normal non-type
// template parameter ('int', 'long', etc.) by an 'enum' type

#if defined(BOOST_MSVC) && BOOST_MSVC < 1300

namespace boost { namespace mpl { namespace aux {
enum ntp { max_value = 0xffffffff };
}}}

#   define BOOST_MPL_AUX_NTP_DECL(T, x) aux::ntp x /**/
#   define BOOST_MPL_AUX_NTP_VALUE(n) aux::ntp(n) /**/

#else

#   define BOOST_MPL_AUX_NTP_DECL(T, x) T x /**/
#   define BOOST_MPL_AUX_NTP_VALUE(n) n /**/

#endif

#endif // BOOST_MPL_AUX_CONFIG_NTP_HPP_INCLUDED
