/* Copyright (c) 2001 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/dst_rules.hpp"
#include "boost/date_time/testfrmwk.hpp"

int
main() 
{
  using namespace boost::posix_time;
  using namespace boost::gregorian;
  date d(2002,Feb,1);
  ptime t(d);

  //The following defines the US dst boundaries, except that the
  //start and end dates are hard coded.
  typedef boost::date_time::us_dst_rules<date, time_duration, 120, 60> us_dst;
  date dst_start(2002,Apr, 7);
  date dst_end(2002,Oct, 27);

  ptime t3a(dst_start, time_duration(2,0,0));   //invalid time label 
  ptime t3b(dst_start, time_duration(2,59,59)); //invalid time label
  ptime t4(dst_start, time_duration(1,59,59));   //not ds 
  ptime t5(dst_start, time_duration(3,0,0));   //always dst
  ptime t6(dst_end, time_duration(0,59,59)); //is dst
  ptime t7(dst_end, time_duration(1,0,0));   //ambiguous
  ptime t8(dst_end, time_duration(1,59,59));   //ambiguous 
  ptime t9(dst_end, time_duration(2,0,0));   //always not dst

  check("dst start", us_dst::local_dst_start_day(2002) == dst_start);
  check("dst end",   us_dst::local_dst_end_day(2002) == dst_end);
  check("dst boundary",   us_dst::is_dst_boundary_day(dst_start));
  check("dst boundary",   us_dst::is_dst_boundary_day(dst_end));
  check("check if time is dst -- not",   
        us_dst::local_is_dst(t.date(), t.time_of_day())==boost::date_time::is_not_in_dst);
  check("label on dst boundary invalid", 
        us_dst::local_is_dst(t3a.date(),t3a.time_of_day())==boost::date_time::invalid_time_label);
  check("label on dst boundary invalid",   
        us_dst::local_is_dst(t3b.date(),t3b.time_of_day())==boost::date_time::invalid_time_label);
   check("check if time is dst -- not",   
         us_dst::local_is_dst(t4.date(),t4.time_of_day())==boost::date_time::is_not_in_dst);
   check("check if time is dst -- yes",   
         us_dst::local_is_dst(t5.date(),t5.time_of_day())==boost::date_time::is_in_dst);

   check("check if time is dst -- not",   
         us_dst::local_is_dst(t6.date(),t6.time_of_day())==boost::date_time::is_in_dst);
   check("check if time is dst -- ambig", 
         us_dst::local_is_dst(t7.date(),t7.time_of_day())==boost::date_time::ambiguous);
   check("check if time is dst -- ambig", 
         us_dst::local_is_dst(t8.date(),t8.time_of_day())==boost::date_time::ambiguous);
   check("check if time is dst -- not",   
         us_dst::local_is_dst(t9.date(),t9.time_of_day())==boost::date_time::is_not_in_dst);


  //Now try a local without dst
  typedef boost::date_time::null_dst_rules<date, time_duration> no_dst_adj;

  check("check null dst rules",   
        no_dst_adj::local_is_dst(t4.date(),t4.time_of_day())==boost::date_time::is_not_in_dst);
  check("check null dst rules",   
        no_dst_adj::local_is_dst(t5.date(),t5.time_of_day())==boost::date_time::is_not_in_dst);
  check("check null dst rules",   
        no_dst_adj::utc_is_dst(t4.date(),t4.time_of_day())==boost::date_time::is_not_in_dst);
  check("check null dst rules",   
        no_dst_adj::utc_is_dst(t5.date(),t5.time_of_day())==boost::date_time::is_not_in_dst);
  

  //Try a southern hemisphere adjustment calculation
  //This is following the rules for South Australia as best I can
  //decipher them.  Basically conversion to DST is last Sunday in
  //October 02:00:00 and conversion off of dst is last sunday in
  //March 02:00:00.  
  //This stuff uses the dst calculator directly...
  date dst_start2(2002,Oct,27); //last Sunday in Oct
  date dst_end2(2002,Mar,31); //last Sunday in March

  typedef boost::date_time::dst_calculator<date,time_duration> dstcalc;
  //clearly not in dst
  boost::date_time::time_is_dst_result a1 =
    dstcalc::local_is_dst(date(2002,May,1),hours(3),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);

  check("check southern not dst",  a1==boost::date_time::is_not_in_dst);

  boost::date_time::time_is_dst_result a2 =
    dstcalc::local_is_dst(date(2002,Jan,1),hours(3),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);

  check("check southern is dst",  a2==boost::date_time::is_in_dst);

  boost::date_time::time_is_dst_result a3 =
    dstcalc::local_is_dst(date(2002,Oct,28),hours(3),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);

  check("check southern is dst",  a3==boost::date_time::is_in_dst);
  boost::date_time::time_is_dst_result a4 =
    dstcalc::local_is_dst(date(2002,Oct,27),time_duration(1,59,59),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-not dst",  a4==boost::date_time::is_not_in_dst);
  boost::date_time::time_is_dst_result a5 =
    dstcalc::local_is_dst(date(2002,Oct,27),hours(3),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-is dst",  a5==boost::date_time::is_in_dst);
  boost::date_time::time_is_dst_result a6 =
    dstcalc::local_is_dst(date(2002,Oct,27),hours(2),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-invalid time",  a6==boost::date_time::invalid_time_label);
  boost::date_time::time_is_dst_result a7 =
    dstcalc::local_is_dst(date(2002,Mar,31),time_duration(0,59,59),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-is dst",  a7==boost::date_time::is_in_dst);
  boost::date_time::time_is_dst_result a8 =
    dstcalc::local_is_dst(date(2002,Mar,31),time_duration(1,0,0),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-ambiguous",  a8==boost::date_time::ambiguous);
  boost::date_time::time_is_dst_result a9 =
    dstcalc::local_is_dst(date(2002,Mar,31),time_duration(1,59,59),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-ambiguous",  a9==boost::date_time::ambiguous);
  boost::date_time::time_is_dst_result a10 =
    dstcalc::local_is_dst(date(2002,Mar,31),time_duration(2,0,0),
                          dst_start2, 120,
                          dst_end2, 120,
                          60);
  check("check southern boundary-not",  a10==boost::date_time::is_not_in_dst);


  printTestStats();
  return 0;
}

/*
 * Copyright (c) 2001
 * CrystalClear Software, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  CrystalClear Software makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided as is without express or implied warranty.
 *
 *
 * Author:  Jeff Garland (jeff@CrystalClearSoftware.com)
 *
 */
