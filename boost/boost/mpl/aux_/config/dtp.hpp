//-----------------------------------------------------------------------------
// boost mpl/aux_/config/dtp.hpp header file
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

#ifndef BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED

// MWCW 7.x-8.0 "losts" default template parameters of nested class 
// templates when their owner classes are passed as arguments to other 
// templates; Borland "forgets" them from the very beginning (if the owner 
// class is a class template).
#if defined(__MWERKS__) && __MWERKS__ <= 0x3001 \
 || defined(__BORLANDC__) && __BORLANDC__ <= 0x551
#   define BOOST_NO_DEFAULT_TEMPLATE_PARAMETERS_IN_NESTED_TEMPLATES
#endif

#endif // BOOST_MPL_AUX_CONFIG_DTP_HPP_INCLUDED
