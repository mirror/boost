#ifndef DATE_TIME_COMPILER_CONFIG_HPP___
#define DATE_TIME_COMPILER_CONFIG_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

// This file performs some local compiler configurations

#include "boost/date_time/locale_config.hpp" //set up locale configurations

//Set up a configuration parameter for platforms that have 
//GetTimeOfDay
#ifdef BOOST_HAS_GETTIMEOFDAY
#define BOOST_DATE_TIME_HAS_GETTIMEOFDAY_HIGH_PRECISION_CLOCK
#endif


#if (defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) || (defined(__BORLANDC__)))
#define BOOST_DATE_TIME_NO_MEMBER_INIT
#endif


// include these types before we try to re-define them
#include "boost/cstdint.hpp"

//Define INT64_C for some Metrowerks compilers
#if (defined(__MWERKS__) && (!defined(INT64_C)))
#define INT64_C(value)  long long(value)
#endif

//Define INT64_C for compilers that don't have it
#if (!defined(INT64_C))
#define INT64_C(value)  int64_t(value)
#endif


/* Workaround for Borland iterator error. Error was "Cannot convert 'istream *' to 'wistream *' in function istream_iterator<>::istream_iterator() */
#if defined(__BORLANDC__) && (__BORLANDC__ <= 0x0551)
#define BOOST_DATE_TIME_NO_WISTREAM_ITERATOR
#endif


// Borland v5.64 does not have the following in std namespace; v5.5.1 does
#if defined(__BORLANDC__) && (__BORLANDC__ >= 0x0564) 
#include <locale>
namespace std {
  using stlport::tolower;
  using stlport::ctype;
  using stlport::use_facet;
}
#endif

/* The following handles the definition of the necessary macros
 * for dll building on Win32 platforms.
 * 
 * For code that will be placed in the date_time .dll, 
 * it must be properly prefixed with BOOST_DATE_TIME_DECL.
 * The corresponding .cpp file must have BOOST_DATE_TIME_SOURCES
 * defined before including its header. For examples see:
 * greg_month.hpp & greg_month.cpp
 * 
 */

#if defined(_MSC_VER) && defined(_DLL)
# define BOOST_DATE_TIME_HAS_DLL_RUNTIME
#endif

// BOOST_DATE_TIME_STATIC_LINK is defined in libs/date_time/build/Jamfile
#if (defined(BOOST_DATE_TIME_HAS_DLL_RUNTIME) && \
     !defined(BOOST_DATE_TIME_STATIC_LINK))
# if defined(BOOST_DATE_TIME_SOURCE)
#  define BOOST_DATE_TIME_DECL __declspec(dllexport)
#  define BOOST_DATE_TIME_BUILD_DLL
# else
#  define BOOST_DATE_TIME_DECL __declspec(dllimport)
# endif
#endif

#ifndef BOOST_DATE_TIME_DECL
# define BOOST_DATE_TIME_DECL
#endif


#endif
