#ifndef _GREGORIAN__CONVERSION_HPP___
#define _GREGORIAN__CONVERSION_HPP___

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/c_time.hpp"

namespace boost {

namespace gregorian {


  //! Converts a date to a tm struct - all associated time components are left unset.
  inline
  tm to_tm(date d) 
  {
    tm datetm;
    boost::gregorian::date::ymd_type ymd = d.year_month_day();
    datetm.tm_year = ymd.year-1900; 
    datetm.tm_mon = ymd.month-1; 
    datetm.tm_mday = ymd.day;
    datetm.tm_wday = d.day_of_week();
    datetm.tm_yday = d.day_of_year()-1;
    datetm.tm_hour = datetm.tm_min = datetm.tm_sec = 0;
    datetm.tm_isdst = -1; //?
    return datetm;
  }

  //! Converts a tm structure into a date dropping the any time values.
  inline
  date date_from_tm(const tm& datetm) 
  {
    return date(datetm.tm_year+1900, datetm.tm_mon+1, datetm.tm_mday);
  }
  

} } //namespace boost::gregorian




#endif

