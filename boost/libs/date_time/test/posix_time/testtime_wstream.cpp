/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Bart Garst
 */
#include <iostream>
#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/testfrmwk.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::gregorian;
using namespace boost::posix_time;
using boost::lexical_cast;

int main(){
  std::wstring res;
  std::wstringstream wss;
  /* time_period was used because all the time-type objects
   * that have operator<< can be easily accessed from it.
   * Tose are: ptime, time_duration, time_period */
  date d1(2003,Jan,20), d2(2003,May,10);
  time_period tp(ptime(d1,hours(1)), ptime(d2,hours(15)));

  // ptime
  wss << tp.begin(); 
  res = lexical_cast<std::wstring>("2003-Jan-20 01:00:00");
  check("ptime", res == wss.str());
  wss.str(lexical_cast<std::wstring>(""));
  // time_duration
  wss << tp.length(); 
  res = lexical_cast<std::wstring>("2654:00:00");
  check("time_duration", res == wss.str());
  wss.str(lexical_cast<std::wstring>(""));
  // time_period
  wss << tp;
#ifdef BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
  res = lexical_cast<std::wstring>("[2003-Jan-20 01:00:00/2003-May-10 14:59:59.999999999]");
#else
  res = lexical_cast<std::wstring>("[2003-Jan-20 01:00:00/2003-May-10 14:59:59.999999]");
#endif
  check("time_period", res == wss.str());
  wss.str(lexical_cast<std::wstring>(""));

  return printTestStats();
}
