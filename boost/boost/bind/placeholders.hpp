#ifndef BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
#define BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED

#if _MSC_VER >= 1020
#pragma once
#endif

//
//  bind/placeholders.hpp - _N definitions
//
//  Copyright (c) 2002 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

#include <boost/bind/arg.hpp>
#include <boost/config.hpp>

// With MSVC precompiled headers, unnamed namespaces are not unique

#ifdef BOOST_MSVC
# define BOOST_BIND_STATIC static
#else
# define BOOST_BIND_STATIC
#endif

namespace
{

BOOST_BIND_STATIC boost::arg<1> _1;
BOOST_BIND_STATIC boost::arg<2> _2;
BOOST_BIND_STATIC boost::arg<3> _3;
BOOST_BIND_STATIC boost::arg<4> _4;
BOOST_BIND_STATIC boost::arg<5> _5;
BOOST_BIND_STATIC boost::arg<6> _6;
BOOST_BIND_STATIC boost::arg<7> _7;
BOOST_BIND_STATIC boost::arg<8> _8;
BOOST_BIND_STATIC boost::arg<9> _9;

} // unnamed namespace

#undef BOOST_BIND_STATIC

#endif // #ifndef BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
