#ifndef POSIX_TIME_CONVERSION_HPP___
#define POSIX_TIME_CONVERSION_HPP___

/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/posix_time/ptime.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
#include "boost/date_time/filetime_functions.hpp"
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

#if defined(BOOST_HAS_FTIME)
  
  //! Function to create a time object from an initialized FILETIME struct.
  /*! Function to create a time object from an initialized FILETIME struct.
   * A FILETIME struct holds 100-nanosecond units (0.0000001). When 
   * built with microsecond resolution the FILETIME's sub second value 
   * will be truncated. Nanosecond resolution has no truncation. 
   *
   * Note ftime is part of the Win32 API, so it is not portable to non-windows
   * platforms.
   */
  template<class time_type>
  inline
  time_type from_ftime(const FILETIME& ft)
  {
    return boost::date_time::time_from_ftime<time_type>(ft);
  }

#endif // BOOST_HAS_FTIME

} } //namespace boost::posix_time




#endif

