

/* Copyright (c) 2003 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland, Bart Garst 
 */

#ifndef BOOST_DATE_TIME_SOURCE
#define BOOST_DATE_TIME_SOURCE
#endif
#include "boost/date_time/date_generators.hpp"

namespace boost {
namespace date_time {

  const char* const _nth_as_str[] = {"out of range", "first", "second",
    "third", "fourth", "fifth"};
    
  //! Returns nth arg as string. 1 -> "first", 2 -> "second", max is 5.
  BOOST_DATE_TIME_DECL const char* nth_as_str(const int ele)
  {
    if(ele >= 1 || ele <= 5) {
      return _nth_as_str[ele];
    } 
    else {
      return _nth_as_str[0];
    }
  }

} } //namespace date_time 




/* Copyright (c) 2003
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

