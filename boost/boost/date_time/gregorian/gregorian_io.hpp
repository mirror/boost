#ifndef DATE_TIME_GREGORIAN_IO_HPP__
#define DATE_TIME_GREGORIAN_IO_HPP__

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

#include "boost/date_time/date_facet.hpp"
#include "boost/date_time/period_formatter.hpp"
#include <iostream>
#include <locale>

namespace boost {
namespace gregorian {


  typedef boost::date_time::period_formatter<wchar_t> wperiod_formatter;
  typedef boost::date_time::period_formatter<char>    period_formatter;
  
  typedef boost::date_time::date_facet<date,wchar_t> wdate_facet;
  typedef boost::date_time::date_facet<date,char>    date_facet;


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date& d) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), d);
    else {
      //instantiate a custom facet for dealing with dates since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every date
      //if the locale did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), d);
    }
    return os;
  }


  template <class charT, class traits>
  inline
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const date_duration& dd)
  {
    os << dd.get_rep();
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::date_period& dp) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), dp);
    else {
      //instantiate a custom facet for dealing with date periods since the user
      //has not put one in the stream so far.  This is for efficiency 
      //since we would always need to reconstruct for every time period
      //if the local did not already exist.  Of course this will be overridden
      //if the user imbues at some later point.  With the default settings
      //for the facet the resulting format will be the same as the
      //std::time_facet settings.
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), dp);

    }
    return os;
  }

  /********** small gregorian types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_month& gm) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), gm);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();//-> 10/1074199752/32 because year & day not initialized in put(...)
      //custom_date_facet* f = new custom_date_facet("%B");
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), gm);
    }
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::greg_weekday& gw) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), gw);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), gw);
    }
    return os;
  }

  /********** date generator types **********/
  
  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::partial_date& pd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), pd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), pd);
    }
    return os;
  }

  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::nth_day_of_the_week_in_month& nkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), nkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), nkd);
    }
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_in_month& fkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fkd);
    }
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::last_day_of_the_week_in_month& lkd) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc()))
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), lkd);
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), lkd);
    }
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_after& fda) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fda);
    } 
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fda);
    }
    return os;
  }


  template <class CharT, class TraitsT>
  inline std::basic_ostream<CharT, TraitsT>&
  operator<<(std::basic_ostream<CharT, TraitsT>& os, const boost::gregorian::first_day_of_the_week_before& fdb) {
    typedef boost::date_time::date_facet<date, CharT> custom_date_facet;
    typedef std::time_put<CharT>                std_date_facet;
    std::ostreambuf_iterator<CharT> oitr(os);
    if (std::has_facet<custom_date_facet>(os.getloc())) {
      std::use_facet<custom_date_facet>(os.getloc()).put(oitr, os, os.fill(), fdb);
    }
    else {
      std::ostreambuf_iterator<CharT> oitr(os);
      custom_date_facet* f = new custom_date_facet();
      std::locale l = std::locale(os.getloc(), f);
      os.imbue(l);
      f->put(oitr, os, os.fill(), fdb);
    }
    return os;
  }

  
} } // namespaces

#endif // DATE_TIME_GREGORIAN_IO_HPP__
