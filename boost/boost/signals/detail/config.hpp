/*
 *
 * Copyright (c) 1998-2002
 * Dr John Maddock
 *
 * Copyright (c) 2003
 * Doug Gregor
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Dr John Maddock makes no representations
 * about the suitability of this software for any purpose.
 * It is provided "as is" without express or implied warranty.
 *
 */

#ifndef BOOST_SIGNALS_LIBRARY_INCLUDE_HPP
#define BOOST_SIGNALS_LIBRARY_INCLUDE_HPP

/*****************************************************************************
 *
 *  Set up dll import/export options:
 *
 ****************************************************************************/
#if defined(_MSC_VER) && defined(_DLL)
#  define BOOST_SIGNALS_HAS_DLL_RUNTIME
#endif

#if defined(BOOST_SIGNALS_HAS_DLL_RUNTIME) && !defined(BOOST_SIGNALS_STATIC_LINK)
#   if defined(BOOST_SIGNALS_IN_LIBRARY_SOURCE)
#       define BOOST_SIGNALS_DECL __declspec(dllexport)
#       define BOOST_SIGNALS_BUILD_DLL
#   else
#       define BOOST_SIGNALS_DECL __declspec(dllimport)
#  endif
#endif

#ifndef BOOST_SIGNALS_DECL
#  define BOOST_SIGNALS_DECL
#endif

/*****************************************************************************
 ****************************************************************************/

#endif // BOOST_SIGNALS_LIBRARY_INCLUDE_HPP









