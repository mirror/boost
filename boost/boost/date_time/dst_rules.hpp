#ifndef DATE_TIME_DST_RULES_HPP__
#define DATE_TIME_DST_RULES_HPP__
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

/*! @file dst_rules.hpp
  Contains template class to provide static dst rule calculations
*/

#include "boost/date_time/date_generators.hpp"
#include "boost/date_time/period.hpp"
#include "boost/date_time/date_defs.hpp"
#include <stdexcept>

namespace boost {
  namespace date_time {

    enum time_is_dst_result {is_not_in_dst, is_in_dst, 
                             ambiguous, invalid_time_label};


    //! Generic functions to calculate dst transition information
    template<class date_type_, 
             class time_duration_type_>
    class dst_calculator
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;

      //! Check the local time offset when on dst start day
      /*! On this dst transition, the time label between
       *  the transition boundary and the boudary + the offset
       *  are invalid times.  If before the boundary then still 
       *  not in dst.  
       *@param time_of_day Time offset in the day for the local time
       *@param dst_start_offset_minutes Local day offset for start of dst
       *@param dst_length_minutes Number of minutes to adjust clock forward
       *@retval status of time label w.r.t. dst
       */
      static time_is_dst_result 
      process_local_dst_start_day(const time_duration_type& time_of_day,
                                  unsigned int dst_start_offset_minutes,
                                  long dst_length_minutes)
      {
        //std::cout << "here" << std::endl;
        if (time_of_day < time_duration_type(0,dst_start_offset_minutes,0)) {
          return is_not_in_dst;
        }
        long offset = dst_start_offset_minutes + dst_length_minutes;
        if (time_of_day >= time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        return invalid_time_label; 
      }

      //! Check the local time offset when on the last day of dst
      /*! This is the calculation for the DST end day.  On that day times
       *  prior to the conversion time - dst_length (1 am in US) are still 
       *  in dst.  Times between the above and the switch time are 
       *  ambiguous.  Times after the start_offset are not in dst.
       *@param time_of_day Time offset in the day for the local time
       *@param dst_end_offset_minutes Local time of day for end of dst
       *@retval status of time label w.r.t. dst
       */
      static time_is_dst_result 
      process_local_dst_end_day(const time_duration_type& time_of_day,
                                unsigned int dst_end_offset_minutes,
                                long dst_length_minutes)
      {
        //in US this will be 60 so offset in day is 1,0,0
        int offset = dst_end_offset_minutes-dst_length_minutes;
        if (time_of_day < time_duration_type(0,offset,0)) {
          return is_in_dst;
        }
        if (time_of_day >= time_duration_type(0,dst_end_offset_minutes,0)) {
          return is_not_in_dst;
        }
        return ambiguous;
      }

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for 
       *  invalid and ambiguous.
       *  @param current_day The day to check for dst
       *  @param time_of_day Time offset within the day to check 
       *  @param dst_start_day  Starting day of dst for the given locality
       *  @param dst_start_offset_minutes Offset within day for dst 
       *         boundary (eg 120 for US which is 02:00:00)
       *  @param dst_end_day    Ending day of dst for the given locality
       *  @param dst_end_offset_minutes Offset within day for dst 
       *         boundary (eg 120 for US which is 02:00:00)
       *  @param dst_length_minutes Length of dst adjusment (eg: 60 for US)
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result 
      local_is_dst(const date_type& current_day,
                   const time_duration_type& time_of_day,
                   const date_type& dst_start_day,
                   unsigned int dst_start_offset_minutes,
                   const date_type& dst_end_day,
                   unsigned int dst_end_offset_minutes,
                   long dst_length_minutes)
      {
        //in northern hemisphere dst is in the middle of the year
        if (dst_start_day < dst_end_day) {
          if ((current_day > dst_start_day) && (current_day < dst_end_day)) {
            return is_in_dst;
          }
          if ((current_day < dst_start_day) || (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
        }
        else {//southern hemisphere dst is at begining /end of year
          if ((current_day < dst_start_day) && (current_day > dst_end_day)) {
            return is_not_in_dst;
          }
          if ((current_day > dst_start_day) || (current_day < dst_end_day)) {
            return is_in_dst;
          }
        }

        if (current_day == dst_start_day) {
          return process_local_dst_start_day(time_of_day,
                                             dst_start_offset_minutes,
                                             dst_length_minutes);
        }
      
        if (current_day == dst_end_day) {
          return process_local_dst_end_day(time_of_day,
                                           dst_end_offset_minutes,
                                           dst_length_minutes);
        }
        //you should never reach this statement
        return invalid_time_label;
      }

    };


    //! Class to calculate dst boundaries for US time zones
    /* 
     */
    template<class date_type_, 
             class time_duration_type_,
             unsigned int dst_start_offset_minutes=120, //from start of day 
             short dst_length_minutes=60>  //1 hour == 60 min in US
    class us_dst_rules
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;
      typedef typename date_type::year_type year_type;
      typedef typename date_type::calendar_type calendar_type;
      typedef date_time::last_kday_of_month<date_type> lkday;
      typedef date_time::first_kday_of_month<date_type> fkday;
      typedef dst_calculator<date_type, time_duration_type> dstcalc;

      //! Calculates if the given local time is dst or not
      /*! Determines if the time is really in DST or not.  Also checks for 
       *  invalid and ambiguous.
       *  @retval The time is either ambiguous, invalid, in dst, or not in dst
       */
      static time_is_dst_result local_is_dst(const date_type& d,
                                             const time_duration_type& td) 
      {

        year_type y = d.year();
        date_type dst_start = local_dst_start_day(y);
        date_type dst_end   = local_dst_end_day(y);
        return dstcalc::local_is_dst(d,td,
                                     dst_start,dst_start_offset_minutes,
                                     dst_end, dst_start_offset_minutes, 
                                     dst_length_minutes);
      
      }


      static bool is_dst_boundary_day(date_type d)
      {
        year_type y = d.year();
        return ((d == local_dst_start_day(y)) ||
                (d == local_dst_end_day(y)));
      }

      static date_type local_dst_start_day(year_type year)
      {
        //first sunday in april
        fkday fsia(Sunday, gregorian::Apr);
        return fsia.get_date(year);      
      }

      static date_type local_dst_end_day(year_type year)
      {
        //last sunday in october
        lkday lsio(Sunday, gregorian::Oct);
        return lsio.get_date(year);
      }

      static time_duration_type dst_offset() 
      {
        return time_duration_type(0,dst_length_minutes,0);
      }

    };



    //! Used for local time adjustments in places that don't use dst
    template<class date_type_, class time_duration_type_>
    class null_dst_rules
    {
    public:
      typedef time_duration_type_ time_duration_type;
      typedef date_type_ date_type;


      //! Calculates if the given local time is dst or not
      /*! @retval Always is_not_in_dst since this is for zones without dst
       */
      static time_is_dst_result local_is_dst(const date_type&, 
                                             const time_duration_type&) 
      {
        return is_not_in_dst;
      }
    
      //! Calculates if the given utc time is in dst
      static time_is_dst_result utc_is_dst(const date_type&, 
                                           const time_duration_type&) 
      {
        return is_not_in_dst;
      }

      static bool is_dst_boundary_day(date_type d)
      {
        return false;
      }

      static time_duration_type dst_offset() 
      {
        return time_duration_type(0,0,0);
      }

    };


  } } //namespace date_time


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
 *
 */

#endif
