/* Copyright (c) 2001 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#ifdef DATE_TIME_INLINE 
  #undef DATE_TIME_INLINE 
  #define DATE_TIME_INLINE inline
#else
  #define DATE_TIME_INLINE
#endif

namespace boost {
namespace date_time {
  //! Return the day of the week (0==Sunday, 1==Monday, etc)
  /*! Converts a the ymd_type into a day of the week number
   */
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  unsigned short
  gregorian_calendar_base<ymd_type_,date_int_type_>::day_of_week(const ymd_type& ymd) 
  {
    unsigned short a = (14-ymd.month)/12;
    unsigned short y = ymd.year - a;
    unsigned short m = ymd.month + 12*a - 2;
    unsigned short d = (ymd.day + y + (y/4) - (y/100) + (y/400) + (31*m)/12) % 7;
    //std::cout << year << "-" << month << "-" << day << " is day: " << d << "\n";
    return d;
  }
  
  //! Convert a ymd_type into a day number
  /*! The day number is an absolute number of days since the start of count
   */
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  date_int_type_
  gregorian_calendar_base<ymd_type_,date_int_type_>::day_number(const ymd_type& ymd) 
  {
    unsigned short a = (14-ymd.month)/12;
    unsigned short y = ymd.year + 4800 - a;
    unsigned short m = ymd.month + 12*a - 3;
    unsigned long  d = ymd.day + ((153*m + 2)/5) + 365*y + (y/4) - (y/100) + (y/400) - 32045;
    return d;
  }

  //! Change a day number into a ymd_type structure
  /*! 
   * 
   */
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  ymd_type_
  gregorian_calendar_base<ymd_type_,date_int_type_>::from_day_number(date_int_type dayNumber) 
  {
    date_int_type a = dayNumber + 32044;
    date_int_type b = (4*a + 3)/146097;
    date_int_type c = a-((146097*b)/4);
    date_int_type d = (4*c + 3)/1461;
    date_int_type e = c - (1461*d)/4;
    date_int_type m = (5*e + 2)/153;
    unsigned short day = e - ((153*m + 2)/5) + 1;
    unsigned short month = m + 3 - 12 * (m/10);
    date_int_type year = 100*b + d - 4800 + (m/10);
    //std::cout << year << "-" << month << "-" << day << "\n";

    return ymd_type(year,month,day);
  }


  //! Determine if the provided year is a leap year
  /*!
   *@return true if year is a leap year, false otherwise
   */
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  bool
  gregorian_calendar_base<ymd_type_,date_int_type_>::is_leap_year(year_type year) 
  {
    //divisible by 4, not if divisible by 100, but true if divisible by 400
    return (!(year % 4))  && ((year % 100) || (!(year % 400)));
  }

  //! Calculate the last day of the month
  /*! Find the day which is the end of the month given year and month
   *  No error checking is performed.
   */
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  unsigned short
  gregorian_calendar_base<ymd_type_,date_int_type_>::end_of_month_day(year_type year, 
				       month_type month) 
  {
    //    switch (month.as_number()) {
    switch (month) {
    case 2:  
      if (is_leap_year(year)) {return 29;}
      else {return 28;};
    case 4: 
    case 6: 
    case 9: 
    case 11: 
      return 30;
    default:
      return 31;
    };
  
  }

  //! Provide the ymd_type specification for the calandar start
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  ymd_type_
  gregorian_calendar_base<ymd_type_,date_int_type_>::epoch()
  {
    return ymd_type(1400,1,1);
  }

  //! Defines length of a week for week calculations
  template<typename ymd_type_, typename date_int_type_>
  DATE_TIME_INLINE
  unsigned short
  gregorian_calendar_base<ymd_type_,date_int_type_>::days_in_week()
  {
    return 7;
  }


} } //namespace gregorian

/* Copyright (c) 2001
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
