#ifndef DATE_TIME_POSIX_TIME_IO_HPP__
#define DATE_TIME_POSIX_TIME_IO_HPP__

/* Copyright (c) 2004-2005 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/time_facet.hpp"
#include "boost/date_time/period_formatter.hpp"
#include "boost/date_time/posix_time/time_period.hpp"
#include "boost/date_time/posix_time/posix_time_duration.hpp"
//#include "boost/date_time/gregorian/gregorian_io.hpp"
#include <iostream>
#include <locale>

namespace boost {
namespace posix_time {


  typedef boost::date_time::time_facet<ptime, wchar_t> wptime_facet;
  typedef boost::date_time::time_facet<ptime, char>     ptime_facet;

  typedef boost::date_time::time_input_facet<ptime,wchar_t> wptime_input_facet;
  typedef boost::date_time::time_input_facet<ptime,char>     ptime_input_facet;


  template <class CharT, class TraitsT>
  inline 
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, 
             const ptime& p) {
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    typedef std::time_put<CharT>                  std_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for ptime
  template <class CharT, class traits>
  inline
  std::basic_istream<CharT, traits>&
  operator>>(std::basic_istream<CharT, traits>& is, ptime& pt)
  {
    typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet;
    std::istreambuf_iterator<CharT,traits> sit(is), str_end;
    if(std::has_facet<time_input_facet>(is.getloc())) {
      std::use_facet<time_input_facet>(is.getloc()).get(sit, str_end, is, pt);
    }
    else {
      time_input_facet* f = new time_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, pt);
    }
    return is;
  }
  

  template <class CharT, class TraitsT>
  inline 
  std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, 
             const boost::posix_time::time_period& p) {
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    typedef std::time_put<CharT>                  std_time_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc())) {
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), p);
    }
    else {
      //instantiate a custom facet for dealing with periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), p);
    }
    return os;
  }

  //! input operator for time_period
  template <class CharT, class traits>
  inline
  std::basic_istream<CharT, traits>&
  operator>>(std::basic_istream<CharT, traits>& is, time_period& tp)
  {
    typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet;
    std::istreambuf_iterator<CharT,traits> sit(is), str_end;
    if(std::has_facet<time_input_facet>(is.getloc())) {
      std::use_facet<time_input_facet>(is.getloc()).get(sit, str_end, is, tp);
    }
    else {
      time_input_facet* f = new time_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, tp);
    }
    return is;
  }
  

  //! ostream operator for posix_time::time_duration 
  //  todo fix to use facet --  place holder for now...
  template <class CharT, class traits>
  inline
  std::basic_ostream<CharT, traits>&
  operator<<(std::basic_ostream<CharT, traits>& os, const time_duration& td)
  {
    typedef boost::date_time::time_facet<ptime, CharT> custom_ptime_facet;
    typedef std::time_put<CharT>                  std_ptime_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_ptime_facet>(os.getloc()))
      std::use_facet<custom_ptime_facet>(os.getloc()).put(oitr, os, os.fill(), td);
    else {
      //instantiate a custom facet for dealing with times since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues as some later point.
      std::ostreambuf_iterator<CharT> oitr(os);
      // TODO create a default time_duration format
      //const CharT fmt[] = {'%', 'H', ':', '%', 'M', ':', '%', 's', '\0'};
      custom_ptime_facet* f = new custom_ptime_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), td);
    }
    return os;
    /*
    typedef boost::date_time::ostream_time_duration_formatter<time_duration, CharT> duration_formatter;
    duration_formatter::duration_put(td, os);
    return os;
    */
  }

  //! input operator for time_duration
  template <class CharT, class traits>
  inline
  std::basic_istream<CharT, traits>&
  operator>>(std::basic_istream<CharT, traits>& is, time_duration& td)
  {
    typedef typename date_time::time_input_facet<ptime, CharT> time_input_facet;
    std::istreambuf_iterator<CharT,traits> sit(is), str_end;
    if(std::has_facet<time_input_facet>(is.getloc())) {
      std::use_facet<time_input_facet>(is.getloc()).get(sit, str_end, is, td);
    }
    else {
      time_input_facet* f = new time_input_facet();
      std::locale l = std::locale(is.getloc(), f);
      is.imbue(l);
      f->get(sit, str_end, is, td);
    }
    return is;
  }
  
} } // namespaces
#endif // DATE_TIME_POSIX_TIME_IO_HPP__
