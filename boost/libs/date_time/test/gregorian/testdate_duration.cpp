/* Copyright (c) 2001 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland, Bart Garst
 */

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/testfrmwk.hpp"
#include <iostream>


void test_date_duration()
{
  using namespace boost::gregorian;
  
  date_duration threeDays(3);
  date_duration twoDays(2);
  //date_duration zeroDays(0);
  check("Self equal case",       threeDays == threeDays);
  check("Not equal case",        !(threeDays == twoDays));
  check("Less case succeed",     twoDays < threeDays);
  check("Not less case",         !(threeDays < twoDays));
  check("Not less case - equal", !(threeDays < threeDays));
  check("Greater than ",         !(threeDays > threeDays));
  check("Greater equal ",        threeDays >= threeDays);
  check("Greater equal - false", !(twoDays >= threeDays));
  check("add", twoDays + threeDays == date_duration(5));
  date_duration fiveDays = threeDays;
  fiveDays += twoDays;
  check("add", fiveDays == date_duration(5));
  date_duration tenDays = fiveDays;
  tenDays += date_duration(5);
  check("add", tenDays.days() == 10);
  
  date_duration derivedOneDay = threeDays - twoDays;
  check("Subtraction - neg result", twoDays - threeDays == date_duration(-1));
  date_duration oneDay(1);
  check("Subtraction",           oneDay == derivedOneDay);
  date_duration fiveDaysDerived = tenDays;
  fiveDaysDerived -= fiveDays;
  check("Subtraction",           fiveDaysDerived == fiveDays);

  oneDay = twoDays / 2;
  check("Division",           oneDay.days() == 1);
  date_duration oneDayDivide = threeDays / 2;
  check("Division",           oneDayDivide.days() == 1);
  date_duration hundred(100);
  hundred /= -10;
  check("Division",           hundred.days() == -10 && hundred.is_negative());

  date_duration pos_dur(123);
  date_duration neg_dur(-pos_dur);
  check("unary-",	neg_dur.days() == -123);
  
  // special values tests
  date_duration pi_dur(pos_infin);
  date_duration ni_dur(neg_infin);
  date_duration nd_dur(not_a_date_time);
  check("pos_inf + neg_inf", 	(pi_dur + ni_dur) == nd_dur);
  //check("inf * integer",	(pi_dur * 2) == pi_dur); // not implemented
  check("neg_inf / integer",	(ni_dur / 3) == ni_dur);
  check("inf + dur",		(pi_dur + hundred) == pi_dur);
  check("unary-",	date_duration(-pi_dur) == ni_dur);
 
//   date_duration dd(1);
//   dd++;
//   check("Increment",             dd == twoDays);

}

int main() {
  test_date_duration();
  return printTestStats();

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
