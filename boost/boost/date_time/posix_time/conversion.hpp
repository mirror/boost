#ifndef POSIX_TIME_CONVERSION_HPP___
#define POSIX_TIME_CONVERSION_HPP___
/* Copyright (c) 2003 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#include "boost/date_time/posix_time/ptime.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/c_time.hpp"

namespace boost {

namespace posix_time {


  //! Function that converts a time_t into a ptime.
  inline
  ptime from_time_t(std::time_t t) 
  {
    ptime start(gregorian::date(1970,1,1));
    return start + seconds(t);
  }


} } //namespace boost::posix_time



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
 *
 */

#endif

