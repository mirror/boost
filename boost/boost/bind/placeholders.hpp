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

namespace
{

boost::arg<1> _1;
boost::arg<2> _2;
boost::arg<3> _3;
boost::arg<4> _4;
boost::arg<5> _5;
boost::arg<6> _6;
boost::arg<7> _7;
boost::arg<8> _8;
boost::arg<9> _9;

} // unnamed namespace

#endif // #ifndef BOOST_BIND_PLACEHOLDERS_HPP_INCLUDED
