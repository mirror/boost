#ifndef DATE_TIME_TIME_DURATION_HPP___
#define DATE_TIME_TIME_DURATION_HPP___
/* Copyright (c) 2000, 2003 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland, Bart Garst
 */

#include "boost/operators.hpp"
#include "boost/date_time/time_defs.hpp"

namespace boost {
namespace date_time {

  //! Simple function to calculate absolute value of a numeric type
  template <typename T> // JDG [7/6/02 made a template]
  inline T absolute_value(T x)
  {
    return x < 0 ? -x : x;
  }

  
  //! Represents some amount of elapsed time measure to a given resolution
  /*! This class represents a standard set of capabilities for all
      counted time durations.  Time duration implementations should derive
      from this class passing their type as the first template parameter.
      This design allows the subclass duration types to provide custom
      construction policies or other custom features not provided here.

      @param T The subclass type
      @param rep_type The time resolution traits for this duration type.
  */
  template<class T, typename rep_type>
  class time_duration : private
      boost::less_than_comparable<T 
    , boost::equality_comparable<T
    > >
  /* dividable, addable, and subtractable operator templates
   * won't work with this class (MSVC++ 6.0). return type 
   * from '+=' is different than expected return type 
   * from '+'. multipliable probably wont work 
   * either (haven't tried) */
  {
  public:
    typedef T duration_type;  //the subclass
    typedef rep_type traits_type;
    typedef typename rep_type::day_type  day_type;
    typedef typename rep_type::hour_type hour_type;
    typedef typename rep_type::min_type  min_type;
    typedef typename rep_type::sec_type  sec_type;
    typedef typename rep_type::fractional_seconds_type fractional_seconds_type;
    typedef typename rep_type::tick_type tick_type;

    time_duration() : ticks_(0) {} 
    time_duration(hour_type hours, 
                  min_type minutes, 
                  sec_type seconds=0,
                  fractional_seconds_type frac_sec = 0) :
      ticks_(rep_type::to_tick_count(hours,minutes,seconds,frac_sec)) 
    {}
    // copy constructor required for dividable<>
    //! Construct from another time_duration (Copy constructor)
    time_duration(const time_duration<T, rep_type>& other)
      : ticks_(other.ticks_){}
    
    //! Returns smallest representable duration
    static duration_type unit()
    {
      return duration_type(0,0,0,1);
    }
    //! Provide the resolution of this duration type
    static time_resolutions resolution()
    {
      return rep_type::resolution();
    }
    //! Returns number of hours in the duration
    hour_type hours()   const
    {
      return (ticks_ / (3600*rep_type::res_adjust()));
    }
    //! Returns normalized number of minutes
    min_type minutes() const
    {
      return absolute_value(((ticks() / (60*rep_type::res_adjust())) % 60));
    }
    //! Returns normalized number of seconds (0..60)
    sec_type seconds() const
    {
      return absolute_value((ticks()/rep_type::res_adjust()) % 60);
    }
    //! Returns total number of seconds truncating any fractional seconds
    sec_type total_seconds() const
    {
      return ticks_ / rep_type::res_adjust();
    }
    //! Returns count of fractional seconds at given resolution
    fractional_seconds_type fractional_seconds() const
    {
      return absolute_value((ticks()%rep_type::res_adjust()));
    }
    //! Returns number of possible digits in fractional seconds
    static unsigned short num_fractional_digits()
    {
      return rep_type::num_fractional_digits();
    }
    duration_type invert_sign() const
    {
      return duration_type(-ticks_); 
    }    
    bool is_negative() const
    {
      return ticks_ < 0;
    }    
    bool operator<(const time_duration& rhs)  const 
    {
      return ticks_ <  rhs.ticks_;
    }
    bool operator==(const time_duration& rhs)  const 
    {
      return ticks_ ==  rhs.ticks_;
    }
    //! unary- Allows for time_duration td = -td1
    duration_type operator-()const
    {
      return duration_type(ticks_ * (-1));
    }
    duration_type operator-(const duration_type& d) const
    {
      return duration_type(ticks_ - d.ticks_);
    }
    duration_type operator+(const duration_type& d) const
    {
      return duration_type(ticks_ + d.ticks_);
    }
    duration_type operator/(int divisor) 
    {
      return duration_type(ticks_ / divisor);
    }
    duration_type operator-=(const duration_type& d)
    {
      ticks_ -= d.ticks_;
      return duration_type(ticks_);
    }
    duration_type operator+=(const duration_type& d)
    {
      ticks_ += d.ticks_;
      return duration_type(ticks_);
    }
    //! Division operations on a duration with an integer.
    duration_type operator/=(int divisor) 
    {
      ticks_ /= divisor;
      return duration_type(ticks_);
    }
    duration_type operator*(int rhs) const
    {
      return duration_type(ticks_ * rhs);
    }
    tick_type ticks() const 
    { 
      return ticks_;
    }

  protected:
    explicit time_duration(tick_type in) : ticks_(in) {};
    tick_type ticks_;
  };



  //! Template for instantiating derived adjusting durations
  /* These templates are designed to work with multiples of
   * 10 for frac_of_second and resoultion adjustment 
   */
  template<class base_duration, long frac_of_second>
  class subsecond_duration : public base_duration
  {
  public:
    typedef typename base_duration::traits_type traits_type;
    explicit subsecond_duration(long ss) :
      base_duration(0,0,0,ss*traits_type::res_adjust()/frac_of_second)
    {}
  };

  
  
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


#endif

