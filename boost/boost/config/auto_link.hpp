//  (C) Copyright John Maddock 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 
 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         auto_link.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Automatic library inclusion for Borland/Microsoft compilers.
  */

/*************************************************************************

USAGE:
~~~~~~

Before including this header you must one or more of define the following macros:

BOOST_LIB_NAME:       Required: A string containing the basename of the library, 
                      for example "boost_regex".
BOOST_DYN_LINK:       Optional: when set link to dll rather than static library.
BOOST_LIB_DIAGNOSTIC: Optional: when set the header will print out the name
                      of the library selected (useful for debugging).

These macros will be undef'ed at the end of the header, further this header
has no include guards - so be sure to include it only once from your library!

Algorithm:
~~~~~~~~~~

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

BOOST_LIB_NAME:       The base name of the lib ( for example boost_regex).

BOOST_LIB_TOOLSET:    The compiler toolset name (vc6, vc7, bcb5 etc).

BOOST_LIB_THREAD_OPT: "s" for single thread builds,
                      "m" for multithread builds.

BOOST_LIB_RT_OPT:     "s" for static runtime,
                      "d" for dynamic runtime.

BOOST_LIB_DEBUG_OPT:  nothing for release builds,
                      "d" for debug builds,
                      "dd" for debug-diagnostic builds (_STLP_DEBUG).

***************************************************************************/

#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifndef BOOST_LIB_NAME
#  error "Macro BOOST_LIB_NAME not set (internal error)"
#endif
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
#if (defined(_DLL) || defined(_RTLDLL)) && defined(BOOST_DYN_LINK)
#  define BOOST_LIB_PREFIX 
#elif defined(BOOST_DYN_LINK)
#  error "Mixing a dll boost library with a static runtime is a really bad idea..."
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
#ifdef BOOST_LIB_DIAGNOSTIC
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
#if defined(BOOST_DYN_LINK)
#  undef BOOST_DYN_LINK
#endif

#endif // _MSC_VER || __BORLANDC__










