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

/*************************************************************************

Libraries for Borland and Microsoft compilers are automatically
selected here, the name of the lib is selected according to the following
formula:

BOOST_LIB_PREFIX
   + BOOST_LIB_NAME
   + "_"
   + BOOST_LIB_TOOLSET
   + "_"
   + BOOST_LIB_THREAD_OPT
   + BOOST_LIB_RT_OPT
   + BOOST_LIB_DEBUG_OPT

These are defined as:

BOOST_LIB_PREFIX:     "lib" for static libraries otherwise "".

BOOST_LIB_NAME:       The base name of the lib (boost_signals).

BOOST_LIB_TOOLSET:    The compiler toolset name (vc6, vc7, bcb5 etc).

BOOST_LIB_THREAD_OPT: "s" for single thread builds,
                      "m" for multithread builds.

BOOST_LIB_RT_OPT:     "s" for static runtime,
                      "d" for dynamic runtime.

BOOST_LIB_DEBUG_OPT:  nothing for release builds,
                      "d" for debug builds,
                      "dd" for debug-diagnostic builds (_STLP_DEBUG).

***************************************************************************/

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

#define BOOST_LIB_NAME "boost_signals"

//
// select toolset:
//
#if defined(BOOST_MSVC) && (BOOST_MSVC == 1200) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

   // vc6-stlport:
#  define BOOST_LIB_TOOLSET "vc6-stlport"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1200)

   // vc6:
#  define BOOST_LIB_TOOLSET "vc6"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1300) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

   // vc6-stlport:
#  define BOOST_LIB_TOOLSET "vc7-stlport"

#elif defined(BOOST_MSVC) && (BOOST_MSVC == 1300)

   // vc7:
#  define BOOST_LIB_TOOLSET "vc7"

#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1310) && (defined(__SGI_STL_PORT) || defined(_STLPORT_VERSION))

   // vc71-stlport:
#  define BOOST_LIB_TOOLSET "vc71-stlport"

#elif defined(BOOST_MSVC) && (BOOST_MSVC >= 1310)

   // vc71:
#  define BOOST_LIB_TOOLSET "vc71"

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x560)

   // CBuilder 6:
#  define BOOST_LIB_TOOLSET "bcb6"

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)

   // CBuilder 6:
#  define BOOST_LIB_TOOLSET "bcb5"

#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x540)

   // CBuilder 6:
#  define BOOST_LIB_TOOLSET "bcb4"

#endif

//
// select thread opt:
//
#if defined(_MT) || defined(__MT__)
#  define BOOST_LIB_THREAD_OPT "m"
#else
#  define BOOST_LIB_THREAD_OPT "s"
#endif

//
// select runtime opt:
//
#if defined(_DLL) || defined(_RTLDLL)
#  define BOOST_LIB_RT_OPT "d"
#else
#  define BOOST_LIB_RT_OPT "s"
#endif

//
// select linkage opt:
//
#if defined(BOOST_SIGNALS_STATIC_LINK) && defined(BOOST_SIGNALS_DYN_LINK)
#  undef BOOST_SIGNALS_STATIC_LINK
#endif
#if (defined(_DLL) || defined(_RTLDLL)) && defined(BOOST_SIGNALS_DYN_LINK)
#  define BOOST_LIB_PREFIX
#else
#  define BOOST_LIB_PREFIX "lib"
#endif

//
// select debug opt:
//
#if defined(BOOST_MSVC) && defined(_DEBUG) && (defined(_STLP_DEBUG) || defined(__STL_DEBUG))
#  define BOOST_LIB_DEBUG_OPT "dd"
#elif defined(BOOST_MSVC) && defined(_DEBUG)
#  define BOOST_LIB_DEBUG_OPT "d"
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x560) && (defined(_STLP_DEBUG) || defined(__STL_DEBUG))
#  define BOOST_LIB_DEBUG_OPT "dd"
#else
#  define BOOST_LIB_DEBUG_OPT
#endif

//
// now include the lib:
//
#if defined(BOOST_LIB_NAME) \
      && defined(BOOST_LIB_PREFIX) \
      && defined(BOOST_LIB_TOOLSET) \
      && defined(BOOST_LIB_THREAD_OPT) \
      && defined(BOOST_LIB_RT_OPT) \
      && defined(BOOST_LIB_DEBUG_OPT)

#  pragma comment(lib, BOOST_LIB_PREFIX BOOST_LIB_NAME "_" BOOST_LIB_TOOLSET "_" BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_DEBUG_OPT ".lib")
#ifdef BOOST_SIGNALS_DIAG
#  pragma message ("Linking to lib file: " BOOST_LIB_PREFIX BOOST_LIB_NAME "_" BOOST_LIB_TOOLSET "_" BOOST_LIB_THREAD_OPT BOOST_LIB_RT_OPT BOOST_LIB_DEBUG_OPT ".lib")
#endif

#endif

//
// finally undef any macros we may have set:
//
#if defined(BOOST_LIB_NAME)
#  undef BOOST_LIB_NAME
#endif
#if defined(BOOST_LIB_TOOLSET)
#  undef BOOST_LIB_TOOLSET
#endif
#if defined(BOOST_LIB_THREAD_OPT)
#  undef BOOST_LIB_THREAD_OPT
#endif
#if defined(BOOST_LIB_RT_OPT)
#  undef BOOST_LIB_RT_OPT
#endif
#if defined(BOOST_LIB_LINK_OPT)
#  undef BOOST_LIB_LINK_OPT
#endif
#if defined(BOOST_LIB_DEBUG_OPT)
#  undef BOOST_LIB_DEBUG_OPT
#endif

#endif // BOOST_SIGNALS_LIBRARY_INCLUDE_HPP









