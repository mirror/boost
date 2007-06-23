/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2007
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_SELECT_COMPILER_INCLUDED
#ifndef BOOST_COMPILER_CONFIG
//#include <boost/config/select_compiler_config.hpp>
//#include BOOST_COMPILER_CONFIG
#include <boost/config.hpp>
#endif
#define BOOST_INTRUSIVE_SELECT_COMPILER_INCLUDED
#endif

#ifdef BOOST_MSVC

   #pragma warning (push)
   //
   //'function' : resolved overload was found by argument-dependent lookup
   //A function found by argument-dependent lookup (Koenig lookup) was eventually 
   //chosen by overload resolution.
   //
   //In Visual C++ .NET and earlier compilers, a different function would have 
   //been called. To pick the original function, use an explicitly qualified name.
   //

   //warning C4275: non dll-interface class 'x' used as base for
   //dll-interface class 'Y'
   #pragma warning (disable : 4275)
   //warning C4251: 'x' : class 'y' needs to have dll-interface to
   //be used by clients of class 'z'
   #pragma warning (disable : 4251)
   #pragma warning (disable : 4675)
   #pragma warning (disable : 4996)
   #pragma warning (disable : 4503)
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4521) ////Disable "multiple copy constructors specified"
   #pragma warning (disable : 4522)
   #pragma warning (disable : 4146)
   #pragma warning (disable : 4267) //conversion from 'X' to 'Y', possible loss of data
#endif

//#define BOOST_INTRUSIVE_USE_ITERATOR_FACADE
//#define BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE
