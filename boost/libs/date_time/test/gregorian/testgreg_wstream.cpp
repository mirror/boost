/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Bart Garst
 */
#include <iostream>
#include <sstream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/testfrmwk.hpp>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;
using namespace boost::gregorian;

int main(){
  std::wstring res;
  std::wstringstream wss;
  /* date_period is used because almost all the date-type objects 
   * that have the operator<< can be easily accessed from it.
   * Those are: date, greg_month, greg_day_of_week,
   * date_period, date_duration (also date_generators) */
  date_period dp(date(2003,Aug,21), date(2004,May,27));
 
  // date
  wss << dp.begin();
  res = lexical_cast<std::wstring>("2003-Aug-21");
  check("date", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // greg_month
  wss << dp.begin().month();
  res = lexical_cast<std::wstring>("08");
  check("greg_month", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // greg_day_of_week
  wss << dp.begin().day_of_week();
  res = lexical_cast<std::wstring>("Thu");
  check("greg_day_of_week", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // date_period
  wss << dp;
  res = lexical_cast<std::wstring>("[2003-Aug-21/2004-May-26]");
  check("date_period", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // date_duration
  wss << dp.length();
  res = lexical_cast<std::wstring>("280");
  check("date_duration", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));

  // special values
  date sv_d(neg_infin);
  date_duration sv_dd(pos_infin);
  // sv-date
  wss << sv_d;
  res = lexical_cast<std::wstring>("-infinity");
  check("date", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // sv-date_duration
  wss << sv_dd;
  res = lexical_cast<std::wstring>("+infinity");
  check("date_duration", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  // sv-date_period
  /*
  wss << sv_dp;
  res = lexical_cast<std::wstring>("[2003-Aug-21/2004-May-26]");
  check("date_period", wss.str() == res);
  std::wcout << wss.str() << std::endl;
  wss.str(lexical_cast<std::wstring>(""));
  */

  // date_generators
  first_day_of_the_week_after fka(Monday);
  wss << fka;
  res = lexical_cast<std::wstring>("Mon after");
  check("first_kday_after", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  
  first_day_of_the_week_before fkb(Monday);
  wss << fkb;
  res = lexical_cast<std::wstring>("Mon before");
  check("first_kday_before", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  
  first_day_of_the_week_in_month fkom(Monday,Jan);
  wss << fkom;
  res = lexical_cast<std::wstring>("first Mon of Jan");
  check("first_kday_of_month", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));
  
  last_day_of_the_week_in_month lkom(Monday,Jan);
  wss << lkom;
  res = lexical_cast<std::wstring>("last Mon of Jan");
  check("last_kday_of_month", wss.str() == res);
  wss.str(lexical_cast<std::wstring>(""));

  return printTestStats();
}
