#ifndef GREGORIAN_FACET_HPP___
#define GREGORIAN_FACET_HPP___
/* Copyright (c) 2002 CrystalClear Software, Inc.
 * Disclaimer & Full Copyright at end of file
 * Author: Jeff Garland 
 */

#include "boost/date_time/gregorian/gregorian_types.hpp"
#include "boost/date_time/date_formatting_locales.hpp" // sets BOOST_DATE_TIME_NO_LOCALE

//This file basically becomes a noop if locales are not supported
#ifndef BOOST_DATE_TIME_NO_LOCALE


namespace boost {
namespace gregorian {

  //! Configuration of the output facet
  struct greg_facet_config
  {
    typedef boost::gregorian::greg_month month_type;
    typedef boost::date_time::special_values special_value_enum;
    typedef boost::gregorian::months_of_year month_enum;
    typedef boost::date_time::weekdays weekday_enum;
  };

  typedef boost::date_time::date_names_put<greg_facet_config> greg_base_facet;
  
  template <class charT, class traits>
  std::basic_ostream<charT, traits>&
  operator<<(std::basic_ostream<charT, traits>& os, const date& d)
  {
    typedef boost::date_time::ostream_date_formatter<date, greg_base_facet, charT> greg_ostream_formatter;
    greg_ostream_formatter::date_put(d, os);
    return os;
  }


} } //namespace gregorian

#endif  
    
    
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
 */
#endif

