#ifndef DATE_TIME_COMPILER_CONFIG_HPP___
#define DATE_TIME_COMPILER_CONFIG_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

// This file performs some local compiler configurations

#include "boost/date_time/locale_config.hpp" //set up locale configurations

#if (defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION) || (defined(__BORLANDC__)))
#define BOOST_DATE_TIME_NO_MEMBER_INIT
#endif

//Define INT64_C for some Metrowerks compilers
#if (defined(__MWERKS__) && (!defined(INT64_C)))
#define INT64_C(value)  long long(value)
#endif

//Work around compilers that don't have std::abs
#if (__GNUC__ <= 3)|| (defined(BOOST_MSVC) && _MSC_VER <= 1200)
#  define BOOST_NO_LONG_LONG_ABS
#endif

#if defined(BOOST_NO_LONG_LONG_ABS)
namespace std
{
    template <typename T> // JDG [7/6/02 made a template]
    inline T abs(T x)
    {
      return x < 0 ? -x : x;
    }
}
#endif

/* Copyright (c) 2002
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */
#endif
